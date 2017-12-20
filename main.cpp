#include <iostream>
#include "sudoku.hpp"

int main(int argc, const char * argv[]) {
  Sudoku::Board board(argv[1]);
  int retval = 2;
  while (true) {
    try {
      board.calculateGuesses();
    } catch (std::string err) {
      std::cout << err << std::endl;
      retval = 1;
      break;
    }
    if (board.confirmGuesses()) {
      std::cout << "Puzzle solved!\n";
      retval = 0;
      break;
    }
  }
  board.saveBoard("result.json");
  return retval;
}