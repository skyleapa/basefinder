#define CATCH_CONFIG_MAIN

#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <vector>

#include "pixelutil/RGBAPixel.h"
#include "pixelutil/PNG.h"
#include "pixelutil/catch.hpp"

#include "decoder.h"
#include "treasureMap.h"

using namespace std;
using namespace pixelutil;


#define IMAGEDIR "images/"
#define SOLNIMGDIR "soln_images/"

/**
 * Test Cases
 */

TEST_CASE("treasureMap::basic no cycles", "[weight=1][part=treasureMap]")
{

	PNG maze;
	maze.readFromFile("images/testimages/snake.png");
	pair<int,int> start(1,1);

    PNG base;
    base.readFromFile("images/testimages/sunshine.png");

    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	treasure.writeToFile("images/testimages/embeddedsnake_out.png");
    PNG treasureans;
    treasureans.readFromFile("images/testimages/embeddedsnake.png");
    REQUIRE( treasure == treasureans );

    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/testimages/greyedsnake_out.png");
    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/testimages/greyedsnake.png");
    REQUIRE( treasuremaze == treasuremazeans );

    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/testimages/solnsnake_out.png");
    PNG solnans;
    solnans.readFromFile("images/testimages/solnsnake.png");
    REQUIRE( soln == solnans );

    PNG solnmaze = dec.renderMaze();
    solnmaze.writeToFile("images/testimages/solnsnakemaze_out.png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/testimages/solnsnakemaze.png");
    REQUIRE( solnmaze == solnmazeans );

}

TEST_CASE("decoder::basic cycles", "[weight=1][part=decoder]")
{
	PNG maze;
	maze.readFromFile("images/testimages/maze.png");
	pair<int,int> start(1,1);

    PNG base;
    base.readFromFile("images/testimages/sunshine.png");

    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	treasure.writeToFile("images/testimages/theembeddedmaze_out.png");
    PNG treasureans;
    treasureans.readFromFile("images/testimages/embeddedmaze.png");
    REQUIRE( treasure == treasureans );

    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/testimages/greyedmaze_out.png");
    PNG treasuremazeans;
	treasuremazeans.readFromFile("images/testimages/greyedmaze.png");
    REQUIRE( treasuremaze == treasuremazeans );

    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/testimages/solnmaze_out.png");
    PNG solnans;
    solnans.readFromFile("images/testimages/solnmaze.png");
    REQUIRE( soln == solnans );

    PNG solnmaze = dec.renderMaze();
    solnmaze.writeToFile("images/testimages/solnmazemaze_out.png");
    PNG solnmazeans;
    solnmazeans.readFromFile("images/testimages/solnmazemaze.png");
    REQUIRE( solnmaze == solnmazeans );

}

TEST_CASE("ea orbital", "[weight=1]") {
	PNG maze;
	maze.readFromFile("images/ea/orbitalmaze.png");
	pair<int,int> start(328,451);

    PNG base;
    base.readFromFile("images/ea/orbitalmap.png");

    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	// treasure.writeToFile("images/ea/orbitalembedded.png");

    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/ea/orbitalgreyed.png");

    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/ea/orbitaldecoded.png");

    // PNG solnmaze = dec.renderMaze();
    // solnmaze.writeToFile("images/ea/orbitalsoln.png");
}

TEST_CASE("ea renewal", "[weight=1]") {
	PNG maze;
	maze.readFromFile("images/ea/renewalmaze.png");
	pair<int,int> start(175, 245);

    PNG base;
    base.readFromFile("images/ea/renewalmap.png");

    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	// treasure.writeToFile("images/ea/renewalembedded.png");

    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/ea/renewalgreyed.png");

    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/ea/renewaldecoded.png");
    
    // PNG solnmaze = dec.renderMaze();
    // solnmaze.writeToFile("images/ea/renewalsoln.png");
}

TEST_CASE("ea breakaway", "[weight=1]") {
	PNG maze;
	maze.readFromFile("images/ea/breakawaymaze.png");
	pair<int,int> start(746, 446);

    PNG base;
    base.readFromFile("images/ea/breakawaymap.png");

    treasureMap M(base, maze, start);

    PNG treasure = M.renderMap();
	// treasure.writeToFile("images/ea/breakawayembedded.png");

    PNG treasuremaze = M.renderMaze();
	treasuremaze.writeToFile("images/ea/breakawaygreyed.png");

    decoder dec(treasure,start);

    PNG soln = dec.renderSolution();
    soln.writeToFile("images/ea/breakawaydecoded.png");
    
    // PNG solnmaze = dec.renderMaze();
    // solnmaze.writeToFile("images/ea/breakawaysoln.png");
}