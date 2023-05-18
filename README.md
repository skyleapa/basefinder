# Base Map Optimizer

Map generation and design is extremely important in games, as it can affect the gameflow and different player strategies. I noticed that in most game maps, different teams have opposing bases placed the furthest apart. This allows players to plan their routes, and endorse map exploration/utilization.

I developed an algorithm based on BFS traversal and distance encoding, which will provide a structured path that simulates where we would expect a base to be on a map. From a specified starting point, the algorithm finds the distances of every pixel on the map's paths, deeming the base to be at the ***longest shortest path*** from the start. It renders the path on the image to visualize where this base would be.

This project was meant to practice my C++ skills and knowledge of algorithms. 

# Theory

Using this program, you can input different maps from all kinds of games, and it can find the best path between the enemy's base, and yours. It does so by finding the **longest shortest path**, which is explained further in the algorithm below. 

## TreasureMap Algorithm

1. The start position of the map is embedded with maze value 0. 
2. The map is based off the base image, and the pixels of the actual map path are modified which aren't visible to the human eye
3. If a point p is embedded with a maze-value v, then p's compass neighbors which are also in the maze and who's value hasnt been set, are embedded with maze value (v+1).

## Stack, Queue, Deque

The basefinder enconding and decoding algorithms utilize a custom stack and queue class based of a modified doubly ended queue structure (deque). The deque uses the C++ vector as an underlying data structure. 

All functions of stack and queue are **O(1)** time. This is possible since every time we remove an element, we check if the size k will fit in the first k empty positions of the vector. If so, we will resize down by copying it into a new vector. Elements can be added or removed on the right side, but only removed on the left side of the deque.

## TreasureMap 

treasureMap.cpp uses a form of image steganography to encode images with a "map". By taking in a starting position, base image and map image, it embeds the base image with the map by the following algorithm.

## Maze Values

Each maze value v can be represent in 6-bit binary. This means v has a value from 0-63, as v=b1b2b3b4b5b6. Each pixel p in the base image has an (r,g,b) value. To embed the base image: 
- The two lower order bits of the binary representation of r are replaced by b1b2. 
- The two lower order bits of g are replaced by b3b4. 
- The two lower order bits of b are replaced by b5b6. 

## Decoder Algorithm

The base or 'treasure' to find is always located at the pixel location whose shortest distance to the start of the map is the longest. decoder.cpp uses breadth first search traversal on an embedded map to find the base. Given the starting point of the map, it will evaluate all of its compass neighbors as having a maze distance of 1 from the current point as we're traversing. We search the maze for the shortest distance from the start to each maze point, then find the longest of those distances which will be the solution. renderSolution then renders the found path to the base as an image. 

## Maze Distance

Each maze distance is computed as follows: Every pixel point p in the image has an r,g,b value. The maze-distance gets the 2 lowest order bits from every r,g,b value from the embedded maze to get the maze-value as explained previously. The maze-distance from p to any of the 4 surrounding pixels is the absolute distance between their maze values. 

# Installation

The project currently uses the maps `orbital`, `breakaway`, and `renewal` as an example from Battlefield 2042. 

_To view these projects, download a local copy onto your computer, and make sure to have [clang](https://clang.llvm.org/get_started.html) before running the makefile using the command below._

```c++
make
./testMaze   
```

_To implement your own maps, from other Battlefield / Frostbite games, upload your images onto `images/ea`, and then navigate to `testMaze.cpp` and implement the following, specific to your new map._

```c++
TEST_CASE("ea NEWMAP", "[weight=1]") {
	PNG maze;
  // the PNG of the map you want to add
	maze.readFromFile("images/ea/orbitalmaze.png");
	pair<int,int> start(328,451);

  // the red map path in which you want to find the route from base A to B
  PNG base;
  base.readFromFile("images/ea/NEWMAPpath.png");

  treasureMap M(base, maze, start);

  PNG treasure = M.renderMap();

  PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/ea/NEWMAPgreyed.png");

  decoder dec(treasure,start);

  PNG soln = dec.renderSolution();
  soln.writeToFile("images/ea/NEWMAPdecoded.png");

}
```

_Test cases are included for the stack and queue, since these are implemented manually. These tests can be run using the command below._
```c++
./testStackQueue
```

# Gallery

Images were sourced here: https://game8.co/games/Battlefield2042/archives/350466
# Breakaway Map 
![](/images/ea/breakawaymap.png) 
![](/images/ea/breakawaymaze.png) 
![](/images/ea/breakawaygreyed.png) 
![](/images/ea/breakawaydecoded.png) 

# Orbital Map 
![](/images/ea/orbital.png) 
![](/images/ea/orbitalmap.png) 
![](/images/ea/orbitalmaze.png) 
![](/images/ea/orbitaldecoded.png)

# Renewal Map 
![](/images/ea/renewal.png) 
![](/images/ea/renewalmap.png) 
![](/images/ea/renewalgreyed.png) 
![](/images/ea/renewaldecoded.png) 




<p align="right">(<a href="#">back to top</a>)</p>

