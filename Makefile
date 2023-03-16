EXE = treasuremap
TESTMAZE = testMaze
TESTSQ = testStackQueue

OBJS_EXE = RGBAPixel.o lodepng.o PNG.o treasureMap.o decoder.o main.o
OBJS_M = RGBAPixel.o lodepng.o PNG.o treasureMap.o decoder.o testMaze.o
OBJS_SQ = testStackQueue.o

CXX = clang++
CXXFLAGS = -std=c++14 -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
#LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm
LDFLAGS = -std=c++14 -lpthread -lm

all : $(EXE) $(TESTSQ) $(TESTMAZE)

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

$(TESTSQ) : $(OBJS_SQ)
	$(LD) $(OBJS_SQ) $(LDFLAGS) -o $(TESTSQ)

$(TESTMAZE) : $(OBJS_M)
	$(LD) $(OBJS_M) $(LDFLAGS) -o $(TESTMAZE)

#object files
testMaze.o : testMaze.cpp pixelutil/PNG.h pixelutil/RGBAPixel.h stack.h queue.h deque.h treasureMap.h treasureMap.cpp decoder.h decoder.cpp
	$(CXX) $(CXXFLAGS) testMaze.cpp

testStackQueue.o : testStackQueue.cpp pixelutil/PNG.h pixelutil/RGBAPixel.h stack.h queue.h deque.h
	$(CXX) $(CXXFLAGS) testStackQueue.cpp

RGBAPixel.o : pixelutil/RGBAPixel.cpp pixelutil/RGBAPixel.h
	$(CXX) $(CXXFLAGS) pixelutil/RGBAPixel.cpp -o $@

PNG.o : pixelutil/PNG.cpp pixelutil/PNG.h pixelutil/RGBAPixel.h pixelutil/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) pixelutil/PNG.cpp -o $@

lodepng.o : pixelutil/lodepng/lodepng.cpp pixelutil/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) pixelutil/lodepng/lodepng.cpp -o $@

treasureMap.o : treasureMap.h treasureMap.cpp pixelutil/RGBAPixel.h pixelutil/PNG.h
	$(CXX) $(CXXFLAGS) treasureMap.cpp -o $@

decoder.o : decoder.h decoder.cpp pixelutil/RGBAPixel.h pixelutil/PNG.h
	$(CXX) $(CXXFLAGS) decoder.cpp -o $@

main.o : main.cpp pixelutil/PNG.h pixelutil/RGBAPixel.h 
	$(CXX) $(CXXFLAGS) main.cpp -o $@

clean :
	-rm -f *.o $(EXE) $(TESTSQ) $(TESTMAZE)
