CXX = g++
CXXFLAGS = -Wall -g

all: src/sudoku.o
	make -C tools
