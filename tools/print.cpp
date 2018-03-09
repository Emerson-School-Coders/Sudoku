#include <iostream>
#include "../src/sudoku.hpp"

int main(int argc, const char * argv[]) {
  const char * location = "result.json";
  if (argc > 1) location = argv[1];
  Sudoku::Board board(location);
  std::cout << "Width: " << board.width << "\nHeight: " << board.height << "\n";
  for (int i = 0; i < board.width; i++) {
    std::cout << "[";
    for (int j = 0; j < board.height; j++) {
        std::cout << (char)(board.grid[i][j] != 0 ? '0' + (char)board.grid[i][j] : ' ') << " ";
    }
    std::cout << "\b]\n";
  }
  return 0;
}
