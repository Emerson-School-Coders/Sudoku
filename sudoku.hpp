#include <json/json.hpp>
#include <vector>
#include <fstream>
#include <string>

namespace Sudoku {
  
  struct Box {
    int x1;
    int y1;
    int x2;
    int y2;
  }

  class Board {
    public:
      int width;
      int height;
      std::vector<std::vector<int> > grid;
      
      Board(int width, int height, int boxcount);
      Board(std::string file);
      Board(const char * file);
      Board(Json::Value json);
      
      void calculateGuesses();
      void confirmGuesses();
      void saveBoard(const char * file);
      void saveBoard(std::string file);
    private:
      int boxWidth;
      int boxHeight;
      int maxNum;
      std::vector<std::vector<std::vector<int> > > guessGrid;
      
      Box getBox(int x, int y);
      std::vector<int> createTemp();
  }
}