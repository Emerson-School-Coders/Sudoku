CXX = g++
CXXFLAGS = -Wall -g

all: solve create print

solve: solve.o ../src/sudoku.o
	$(CXX) $(CXXFLAGS) -o solve solve.o ../src/sudoku.o -ljsoncpp

create: create.o
	$(CXX) $(CXXFLAGS) -o create create.o -ljsoncpp

print: print.o ../src/sudoku.o
	$(CXX) $(CXXFLAGS) -o print print.o ../src/sudoku.o -ljsoncpp

solve.o: solve.cpp ../src/sudoku.hpp

create.o: create.cpp ../src/sudoku.hpp

print.o: print.cpp ../src/sudoku.hpp
