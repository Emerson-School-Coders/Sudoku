#include <iostream>
#include "../src/sudoku.hpp"

int main(int argc, const char * argv[]) {
  Sudoku::Board board(argv[1]);
  int retval = 2;
  std::cout << "Trying old algorithm\n";
  int g = 1;
  while (true) {
    try {
      std::cout << "Guess #" << g << "\n";
      board.calculateGuesses_old();
    } catch (std::string err) {
      std::cout << err << std::endl;
      retval = 1;
      break;
    }
    if (board.confirmGuesses_old()) {
      std::cout << "Puzzle solved!\n";
      retval = 0;
      break;
    }
    g++;
  }
  std::cout << "Trying new algorithm\n";
  g = 1;
  while (true) {
    std::cout << "Guess #" << g << "\n";
    board.calculateGuesses_new();
    int r = board.confirmGuesses_new();
    if (r == 1) {
      std::cout << "Puzzle unsolvable!\n";
      retval = 1;
      break;
    } else if (r == 2) {
      std::cout << "Puzzle solved!\n";
      retval = 0;
      break;
    }
    g++;
  }
  board.saveBoard("result.json");
  return retval;
}
