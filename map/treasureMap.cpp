#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG &baseim, const PNG &mazeim, pair<int, int> s)
{
    base = baseim;
    maze = mazeim;
    start = s;
}

void treasureMap::setGrey(PNG &im, pair<int, int> loc)
{
    int x = loc.first;
    int y = loc.second;

    RGBAPixel *pixel = im.getPixel(x, y);
    pixel->r = 2 * (pixel->r / 4);
    pixel->g = 2 * (pixel->g / 4);
    pixel->b = 2 * (pixel->b / 4);
}

void treasureMap::setLOB(PNG &im, pair<int, int> loc, int d)
{
    int x = loc.first;
    int y = loc.second;
    unsigned char six_bits = d % 64;

    unsigned char red_bits = 48;
    unsigned char green_bits = 12;
    unsigned char blue_bits = 3;

    unsigned char red = (six_bits & red_bits) >> 4;
    unsigned char green = (six_bits & green_bits) >> 2;
    unsigned char blue = six_bits & blue_bits;

    RGBAPixel *pixel = im.getPixel(x, y);

    unsigned char last_two = 252;

    pixel->r = ((pixel->r & last_two) | red);
    pixel->g = ((pixel->g & last_two) | green);
    pixel->b = ((pixel->b & last_two) | blue);
}

PNG treasureMap::renderMap()
{
    // 0. Make copy of base image
    PNG base_copy = PNG(base);

    // 1. Initialize working vectors
    vector<vector<bool>> visited;
    vector<vector<int>> paths;

    vector<bool> temp1;
    vector<int> temp2;

    for (int x = 0; x < base.width(); x++)
    {
        temp1.push_back(false);
        temp2.push_back(1);
    }

    for (int y = 0; y < base_copy.height(); y++)
    {
        visited.push_back(temp1);
        paths.push_back(temp2);
    }

    // 2. Initialize queue
    Queue<pair<int, int>> to_visit;

    // 3. Setup start location
    visited[start.second][start.first] = true;
    paths[start.second][start.first] = 0;
    setLOB(base_copy, start, 0);
    to_visit.enqueue(start);

    // 4. Traverse maze, update the map
    while (!to_visit.isEmpty())
    {
        pair<int, int> curr = to_visit.dequeue();
        vector<pair<int, int>> neighbours = neighbors(curr);

        int distance = paths[curr.second][curr.first];

        for (int i = 0; i < 4; i++)
        {
            pair<int, int> neighbour = neighbours[i];
            if (good(visited, curr, neighbour))
            {
                visited[neighbour.second][neighbour.first] = true;
                paths[neighbour.second][neighbour.first] = distance + 1;
                setLOB(base_copy, neighbour, distance + 1);
                to_visit.enqueue(neighbour);
            }
        }
    }

    // 5. Return the image
    return base_copy;
}

PNG treasureMap::renderMaze()
{
    // Path
    PNG base_copy = PNG(base);
    vector<vector<bool>> visited;
    Queue<pair<int, int>> to_visit;
    vector<bool> temp;

    for (int x = 0; x < base_copy.width(); x++)
    {
        temp.push_back(false);
    }

    for (int y = 0; y < base_copy.height(); y++)
    {
        visited.push_back(temp);
    }

    visited[start.second][start.first] = true;
    setGrey(base_copy, start);
    to_visit.enqueue(start);

    while (!to_visit.isEmpty())
    {
        pair<int, int> curr = to_visit.dequeue();
        vector<pair<int, int>> neighbours = neighbors(curr);

        for (int i = 0; i < 4; i++)
        {
            if (good(visited, curr, neighbours[i]))
            {
                visited[neighbours[i].second][neighbours[i].first] = true;
                setGrey(base_copy, neighbours[i]);
                to_visit.enqueue(neighbours[i]);
            }
        }
    }

    // Starting square
    int start_x = start.first;
    int start_y = start.second;

    for (int y = start_y - 3; y <= start_y + 3; y++)
    {
        for (int x = start_x - 3; x <= start_x + 3; x++)
        {
            if (x >= 0 && x < base_copy.width() && y >= 0 && y < base_copy.height())
            {
                RGBAPixel *pixel = base_copy.getPixel(x, y);
                pixel->r = 255;
                pixel->g = 0;
                pixel->b = 0;
            }
        }
    }

    return base_copy;
}

bool treasureMap::good(vector<vector<bool>> &v, pair<int, int> curr, pair<int, int> next)
{
    // 1. Within the image
    int x = next.first;
    int y = next.second;

    if (x < 0 || y < 0 || x >= maze.width() || y >= maze.height())
    {
        return false;
    }

    // 2. Unvisited
    if (v[y][x])
        return false;

    // 3. Same colour as curr in the maze image
    RGBAPixel *pixel_curr = maze.getPixel(curr.first, curr.second);
    RGBAPixel *pixel_next = maze.getPixel(next.first, next.second);
    if ((pixel_curr->r != pixel_next->r) || (pixel_curr->g != pixel_next->g) || (pixel_curr->b != pixel_next->b))
    {
        return false;
    }

    return true;
}

vector<pair<int, int>> treasureMap::neighbors(pair<int, int> curr)
{
    vector<pair<int, int>> neighbours;

    pair<int, int> left;
    pair<int, int> below;
    pair<int, int> right;
    pair<int, int> above;

    left.first = curr.first - 1;
    left.second = curr.second;

    below.first = curr.first;
    below.second = curr.second + 1;

    right.first = curr.first + 1;
    right.second = curr.second;

    above.first = curr.first;
    above.second = curr.second - 1;

    neighbours.push_back(left);
    neighbours.push_back(below);
    neighbours.push_back(right);
    neighbours.push_back(above);

    return neighbours;
}
