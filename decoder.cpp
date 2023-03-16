#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG &tm, pair<int, int> s)
    : start(s), mapImg(tm)
{
   int rows = mapImg.height();
   int cols = mapImg.width();

   vector<vector<bool>> visited(rows, vector<bool>(cols, 0));                              // Vector containing visited values
   vector<vector<int>> shortestPath(rows, vector<int>(cols, 0));                           // vector containing shortest path
   vector<vector<pair<int, int>>> discovery(rows, vector<pair<int, int>>(cols, {-1, -1})); // vector containing where path length
                                                                                           // was first discovered from
   Queue<pair<int, int>> toExplore;

   visited[start.second][start.first] = true;
   shortestPath[start.second][start.first] = 0;

   toExplore.enqueue(start);
   int currDistance = 0;
   pair<int, int> curr;
   pair<int, int> furthest = start;

   while (!toExplore.isEmpty())
   {
      curr = toExplore.dequeue();
      currDistance = shortestPath[curr.second][curr.first];
      RGBAPixel *currPixel = mapImg.getPixel(curr.first, curr.second);
      vector<pair<int, int>> neighborsList = neighbors(curr);

      // goes through all the neighbors and decodes them
      for (int i = 0; i < neighborsList.size(); i++)
      {
         pair<int, int> p = neighborsList[i];
         if (good(visited, shortestPath, curr, p))
         {
            visited[p.second][p.first] = true;
            shortestPath[p.second][p.first] = currDistance + 1;
            if (shortestPath[furthest.second][furthest.first] <= currDistance + 1)
            {
               furthest = p;
            }
            // 1) if shortest path of whatever discovery is populated with is better then don't change
            discovery[p.second][p.first] = curr;
            toExplore.enqueue(p);
         }
      }
      currDistance++;
   }

   pair<int, int> currPair = furthest;
   pathPts.insert(pathPts.begin(), currPair);
   while (currPair != start)
   {
      currPair = discovery[currPair.second][currPair.first];
      pathPts.insert(pathPts.begin(), currPair);
   }
}

PNG decoder::renderSolution()
{
   for (int i = 0; i < pathPts.size(); i++)
   {
      RGBAPixel *curr = mapImg.getPixel(pathPts[i].first, pathPts[i].second);
      curr->r = 255;
      curr->g = 0;
      curr->b = 0;
   }
   return mapImg;
}

PNG decoder::renderMaze()
{
   int rows = mapImg.height(); // 1.
   int columns = mapImg.width();

   vector<vector<bool>> visited(rows, vector<bool>(columns, 0));
   vector<vector<int>> shortestPath(rows, vector<int>(columns, 0));

   Queue<pair<int, int>> toExplore; // 2.

   visited[start.second][start.first] = true; // the start point
   shortestPath[start.second][start.first] = 0;
   setGrey(mapImg, start);

   toExplore.enqueue(start);
   int currDistance = 0;
   pair<int, int> curr;

   while (!toExplore.isEmpty())
   {
      curr = toExplore.dequeue();
      currDistance = shortestPath[curr.second][curr.first];
      RGBAPixel *currPixel = mapImg.getPixel(curr.first, curr.second);
      vector<pair<int, int>> neighboursList = neighbors(curr);
      for (int i = 0; i < neighboursList.size(); i++)
      {
         pair<int, int> p = neighboursList[i];
         if (good(visited, shortestPath, curr, p))
         {
            visited[p.second][p.first] = true;
            shortestPath[p.second][p.first] = currDistance + 1;
            setGrey(mapImg, p);
            toExplore.enqueue(p);
         }
      }
      currDistance++;
   }

   int y_boundary = min(start.second + 3, (int)mapImg.height() - 1);
   int x_boundary = min(start.first + 3, (int)mapImg.width() - 1);
   int y_lowerbound = max(start.second - 3, 0);
   int x_lowerbound = max(start.first - 3, 0);

   for (unsigned x = x_lowerbound; x <= x_boundary; x++)
   {
      for (unsigned y = y_lowerbound; y <= y_boundary; y++)
      {
         RGBAPixel *currPixel = mapImg.getPixel(x, y);
         currPixel->r = 255;
         currPixel->g = 0;
         currPixel->b = 0;
      }
   }

   return mapImg;
}

void decoder::setGrey(PNG &im, pair<int, int> loc)
{

   RGBAPixel *basePixel = im.getPixel(loc.first, loc.second);
   basePixel->r = (unsigned char)2 * (basePixel->r / 4);
   basePixel->g = (unsigned char)2 * (basePixel->g / 4);
   basePixel->b = (unsigned char)2 * (basePixel->b / 4);
}

pair<int, int> decoder::findSpot()
{
   return pathPts[pathPts.size()];
}

int decoder::pathLength()
{
   return pathPts.size();
}

bool decoder::good(vector<vector<bool>> &v, vector<vector<int>> &d, pair<int, int> curr, pair<int, int> next)
{
   // Criteria:
   // 1. within the image
   // 2. unvisited, and
   // 3. the same colour as curr in the maze image (member var)

   // 1
   bool withinx = next.first >= 0 && next.first < mapImg.width();
   bool withiny = next.second >= 0 && next.second < mapImg.height();
   bool within = withinx && withiny;
   if (!within)
   {
      return false;
   }
   // 2
   bool unvisited = !v[next.second][next.first];

   // 3
   RGBAPixel *nextpixel = mapImg.getPixel(next.first, next.second);
   bool colorcheck = compare(*nextpixel, d[curr.second][curr.first]);

   return within && unvisited && colorcheck;
}

vector<pair<int, int>> decoder::neighbors(pair<int, int> curr)
{

   vector<pair<int, int>> neighbours;

   pair<int, int> north = {curr.first, curr.second - 1};
   pair<int, int> south = {curr.first, curr.second + 1};
   pair<int, int> east = {curr.first + 1, curr.second};
   pair<int, int> west = {curr.first - 1, curr.second};

   neighbours.push_back(west);
   neighbours.push_back(south);
   neighbours.push_back(east);
   neighbours.push_back(north);

   return neighbours;
}

bool decoder::compare(RGBAPixel p, int d)
{

   int lowerbits = (d + 1) % 64;
   bool rCheck = p.r % 4 == (lowerbits >> 4) % 4;
   bool gCheck = p.g % 4 == (lowerbits >> 2) % 4;
   bool bCheck = p.b % 4 == lowerbits % 4;

   return rCheck && gCheck && bCheck;
}
