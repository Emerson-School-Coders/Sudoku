#include "sudoku.hpp"
//#include <iostream>

int floordiv(int divisor, int dividend) {
	return (divisor - (divisor % dividend)) / dividend;
}

namespace Sudoku {

  Board::Board(int w, int h, int boxw, int boxh): width(w), height(h), boxWidth(boxw), boxHeight(boxh) {
    maxNum = boxw*boxh;
  }
  
  Board::Board(std::string file) {
    Json::Value root;
    std::ifstream in;
    in.open(file.c_str());
    in >> root;
    in.close();
    width = root["width"].asInt();
    height = root["height"].asInt();
    boxWidth = root["boxWidth"].asInt();
    boxHeight = root["boxHeight"].asInt();
    maxNum = root["maxNum"].asInt();
    Json::Value g = root["maxNum"];
    for (int i = 0; i < g.size(); i++) {
      for (int j = 0; j < g[i].size(); j++) {
        grid[i][j] = g[i][j].asInt();
      }
	}
  }
  
  Board::Board(const char * file) {
    Json::Value root;
    std::ifstream in;
    in.open(file);
    in >> root;
    in.close();
    width = root["width"].asInt();
    height = root["height"].asInt();
    boxWidth = root["boxWidth"].asInt();
    boxHeight = root["boxHeight"].asInt();
    maxNum = root["maxNum"].asInt();
    Json::Value g = root["grid"];
    //std::cout << g;
    for (int i = 0; i < g.size(); i++) {
      std::vector<int> temp;
      for (int j = 0; j < g[i].size(); j++) {
      	//std::cout << "i=" << i << " j=" << j << "\n";
        temp.push_back(g[i][j].asInt());
      }
      grid.push_back(temp);
    }
  }

  Board::Board(Json::Value root) {
    width = root["width"].asInt();
    height = root["height"].asInt();
    boxWidth = root["boxWidth"].asInt();
    boxHeight = root["boxHeight"].asInt();
    maxNum = root["maxNum"].asInt();
    Json::Value g = root["maxNum"];
    for (int i = 0; i < g.size(); i++) {
      for (int j = 0; j < g[i].size(); j++) {
        grid[i][j] = g[i][j].asInt();
      }
    }
  }


  Box Board::getBox(int x, int y) {
    Box retval;
    retval.x1 = x - (x % boxWidth);
    retval.y1 = y - (y % boxHeight);
    retval.x2 = retval.x1 + boxWidth - 2;
    retval.y2 = retval.y1 + boxHeight - 2;
    return retval;
  }
  
  std::vector<int> Board::createTemp() {
    std::vector<int> retval;
    for (int i = 1; i <= maxNum; i++) retval.push_back(i);
    return retval;
  }
  
  void Board::calculateGuesses_old() {
    bool finished = false;
    //for (std::vector<int> i : grid) {for (int j : i) std::cout << j << ", "; std::cout << "\b\n";}
    guessGrid.resize(6);
    for (int i = 0; i < grid.size(); i++) {
      //std::cout << i << "\n";
      guessGrid[i].resize(6);
      for (int j = 0; j < grid[i].size(); j++) {
        if (grid[i][j] == 0) {
          std::vector<int> retval = this->createTemp();
          std::vector<int> remove;
          // First check the current row
          for (int k = 0; k < width; k++) {
            for (int l = 0; l < retval.size(); l++) {
              //std::cout << "grid[" << k << "][" << j << "] = " << grid[k][j] << "\n";
              if (0 != grid[k][j]) remove.push_back(grid[k][j]);
            }
          }
         // std::cout << "\n";
          // Then check the current column
          for (int m = 0; m < height; m++) {
            for (int n = 0; n < retval.size(); n++) {
              //std::cout << "grid[" << i << "][" << m << "] = " << grid[i][m] << "\n";
              if (0 != grid[i][m]) remove.push_back(grid[i][m]);
            }
          }
          // Finally check the box
          Box current = this->getBox(i, j);
          //std::cout << "Bounds: (" << current.x1 << ", " << current.y1 << "), (" << current.x2 << ", " << current.y2 << ")\n";
          for (int o = current.x1; o <= current.x2; o++) {
            for (int p = current.y1; p <= current.y2; p++) {
              if (0 != grid[o][p]) remove.push_back(grid[o][p]);
            }
          }
          //std::cout << "Removing: ";
          for (int v = 0; v < remove.size(); v++) {
            //std::cout << remove[v] << ", ";
          	for (int w = 0; w < retval.size(); w++) {
          	  if (remove[v] == retval[w]) retval.erase(retval.begin() + w);
          	}
          }
          // Check if puzzle is unsolvable
          //std::cout << "Guesses for " << i << ", " << j << ": ";
          //for (int guess : retval) std::cout << guess << ", ";
       	  //std::cout << "\n";
          if (retval.size() == 0) throw std::string("Puzzle is unsolvable!");
          guessGrid[i][j] = retval;
          if (retval.size() > 1 && i != grid.size() - 1 && j != grid[i].size() - 1) finished = true;
          else if (retval.size() > 1 && finished) finished = true;
          else finished = false;
        } else guessGrid[i][j] = std::vector<int>();
        //std::cout << "Guesses for " << i << ", " << j << ": ";
        //for (int guess : guessGrid[i][j]) std::cout << guess << ", ";
        //std::cout << "\n";
      }
    }
    if (finished) throw std::string("Puzzle is fully solved!");
  }

	void Board::calculateGuesses_new() {
		// Get required numbers for rows
		for (int i = 0; i < grid.size(); i++) {
			std::vector<int> reqs;
			for (int f = 1; f <= maxNum; f++) reqs.push_back(f);
			for (int j : grid[i]) 
				for (int r = 0; r < reqs.size(); r++) 
					if (j == reqs[r]) 
						reqs.erase(reqs.begin() + r--);
			row_requirements[i] = reqs;
		}
		// Get required numbers for columns
		for (int i = 0; i < grid[0].size(); i++) {
			std::vector<int> reqs;
			for (int f = 1; f <= maxNum; f++) reqs.push_back(f);
			for (int j = 0; j < grid.size(); j++) 
				for (int r = 0; r < reqs.size(); r++) 
					if (grid[j][i] == reqs[r]) 
						reqs.erase(reqs.begin() + r--);
			column_requirements[i] = reqs;
		}
		for (int i = 0; i < grid.size(); i += boxWidth) {
			for (int j = 0; j < grid[i].size(); j += boxHeight) {
				std::vector<int> reqs;
				for (int f = 1; f <= maxNum; f++) reqs.push_back(f);
				for (int k = 0; k < boxWidth; k++) 
					for (int l = 0; l < boxHeight; l++) 
						for (int r = 0; r < reqs.size(); r++) 
							if (grid[i+k][j+l] == reqs[r]) 
								reqs.erase(reqs.begin() + r);
				box_requirements[floordiv(i, boxWidth)][floordiv(j, boxHeight)] = reqs;
			}
		}
	}
  
  bool Board::confirmGuesses_old() {
    for (int i = 0; i < guessGrid.size(); i++)
      for (int j = 0; j < guessGrid[i].size(); j++)
        if (guessGrid[i][j].size() == 1) grid[i][j] = guessGrid[i][j][0];
    guessGrid.clear();
    for (std::vector<int> k : grid) for (int l : k) if (l == 0) return false;
    return true;
  }
	
	int Board::confirmGuesses_new() {
		int ret = 2;
		for (int i = 0; i < grid.size(); i++) {
			for (int j = 0; j < grid[i].size(); j++) {
				std::vector<int> reqs = row_requirements[i];
				std::vector<int> keepc;
				for (int c : column_requirements[j])
					for (int r : reqs) 
						if (r == c) 
							keepc.push_back(r);
				reqs = keepc;
				std::vector<int> keepb;
				for (int bc : box_requirements[floordiv(i, boxWidth)][floordiv(j, boxHeight)])
					for (int r : reqs)
						if (r == bc)
							keepb.push_back(r);
				reqs = keepc;
				if (reqs.size() == 1) {
					grid[i][j] = reqs[0];
					ret = 0;
				}
				else if (reqs.size() == 0) return 1;
			}
		}
		return ret;
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
      Json::Value temp(Json::arrayValue);
      for (int j = 0; j < grid[i].size(); j++) {
        temp.append(grid[i][j]);
      }
      root["grid"].append(temp);
    }
    std::ofstream out;
    out.open(file);
    out << root;
    out.close();
  }
  
  void Board::saveBoard(std::string file) {
    this->saveBoard(file.c_str());
  }
}
