CXX = g++

objects = board.o

build : $(objects)
	$(CXX) -g main.cpp $(objects)

board.o : board.cpp
	$(CXX) -c -ggdb board.cpp board.h


