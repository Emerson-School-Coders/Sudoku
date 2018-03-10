#include <json/json.h>
#include <vector>
#include <fstream>
#include <string>
#include <utility>

namespace Sudoku {
  
  struct Box {
    int x1;
    int y1;
    int x2;
    int y2;
  };

  class Board {
    public:
      int width;
      int height;
      std::vector<std::vector<int> > grid;
      
      Board(int width, int height, int boxw, int boxh);
      Board(std::string file);
      Board(const char * file);
      Board(Json::Value root);
      
      void calculate_guess();
      bool confirm_guess();
      void calculate_eliminate();
      int confirm_eliminate();
      void calculate_crosshatch();
      int confirm_crosshatch();
      void saveBoard(const char * file);
      void saveBoard(std::string file);
    private:
      int boxWidth;
      int boxHeight;
      int maxNum;
      bool unsolv;
      std::vector<std::vector<std::vector<int> > > guessGrid;
    
      std::vector<std::vector<int> > row_requirements;
      std::vector<std::vector<int> > column_requirements;
      std::vector<std::vector<std::vector<int> > > box_requirements;
      
      std::vector<std::vector<std::vector<std::vector<std::pair<int, int> > > > > crosshatch;
      
      Box getBox(int x, int y);
      std::vector<int> createTemp();
  };
}
