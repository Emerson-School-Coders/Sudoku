#include "sudoku.hpp"

namespace Sudoku {

  Board::Board(int w, int h, int boxw, int boxh): width(w), height(h), boxWidth(boxw), boxHeight(boxh) {
    maxNum = boxw*boxh;
  }
  
  Board::Board(std::string file) {
    Json::Reader reader;
    Json::Value root;
    bool pSuccess = reader.parse(file, root);
    if (pSuccess) {
      this = Board(root);
    } else {
      width = 0;
      height = 0;
      boxWidth = 0;
      boxHeight = 0;
    maxNum = 0;
    }
  }
  
  Board::Board(const char * file) {
    this = Board(std::string(file));
  }

  Board::Board(Json::Value json) {
    width = root['width'].asInt();
    height = root['height'].asInt();
    boxWidth = root['boxWidth'].asInt();
    boxHeight = root['boxHeight'].asInt();
    maxNum = root['maxNum'].asInt();
    Json::Value g = root['maxNum'];
    for (int i = 0; i < g.size(); i++) {
      for (int j = 0; j < g[i].size(); j++) {
        grid[i][j] = g[i][j].asInt();
      }
    }
  }


  Box Board::getBox(int x, int y) {
    Box retval;
    retval.x1 = x - (x % boxWidth) + 1;
    retval.y1 = y - (y % boxHeight) + 1;
    retval.x2 = retval.x1 + boxWidth - 1;
    retval.y2 = retval.y1 + boxHeight - 1;
    return retval;
  }
  
  std::vector<int> Board::createTemp() {
    std::vector<int> retval;
    for (int i = 1; i <= maxNum; i++) retval.push_back(i);
    return retval;
  }
  
  void Board::calculateGuesses() {
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[i].size(); j++) {
        if (grid[i][j] == 0) {
          std::vector<int> retval = this->createTemp();
          // First check the current row
          for (int k = 0; k < width; k++)
            for (int l = 0; l < retval.size(); l++)
              if (retval[l] == grid[k][j]) retval.erase(retval.begin() + l);
          // Then check the current column
          for (int m = 0; m < height; m++)
            for (int n = 0; n < retval.size(); n++)
              if (retval[n] == grid[i][m]) retval.erase(retval.begin() + n);
          // Finally check the box
          Box current = this->getBox(i, j);
          for (int o = current.x1; o <= current.x2; o++)
            for (int p = current.y1; p <= current.y2; p++)
              for (int q = 0; q < retval.size(); q++)
                if (retval[q] == grid[o][p]) retval.erase(retval.begin() + q);
          // Check if puzzle is unsolvable
          if (retval.size() == 0) throw std::string("Puzzle is unsolvable!");
          guessGrid[i][j] = retval;
        } else guessGrid[i][j] = std::vector<int>();
      }
    }
  }
  
  bool Board::confirmGuesses() {
    for (int i = 0; i < guessGrid.size(); i++)
      for (int j = 0; j < guessGrid[i].size(); j++)
        if (guessGrid[i][j].size() == 1) grid[i][j] = guessGrid[i][j][0];
    guessGrid.clear();
    for (std::vector<int> k : grid) for (int l : k) if (l == 0) return false;
    return true;
  }
  
  void Board::saveBoard(const char * file) {
    Json::Value root(Json::objectValue);
    root["width"] = width;
    root["height"] = height;
    root["boxWidth"] = boxWidth;
    root["boxHeight"] = boxHeight;
    root["maxNum"] = maxNum;
    root["grid"] = Json::Value(Json::arrayValue);
    for (int i = 0; i < grid.size(); i++) {
      root["grid"][i] = Json::Value(Json::arrayValue);
      for (int j = 0; j < grid[i].size(); j++) {
        root["grid"][i][j] = grid[i][j];
      }
    }
    Json::StreamWriter writer;
    std::ofstream out;
    out.open(file);
    writer.write(root, &out);
    out.close();
  }
  
  void Board::saveBoard(std::string file) {
    this->saveBoard(file.c_str());
  }
}
