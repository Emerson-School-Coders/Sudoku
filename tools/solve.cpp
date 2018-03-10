#include <iostream>
#include "../src/sudoku.hpp"

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <file.json>\n";
        return 1;
    }
    Sudoku::Board board(argv[1]);
    int retval = 2;
    int ga, gb, gc;
    int guess_ret;
    int elim_ret;
    int cross_ret;
    while (true) {
        ga = 1;
        std::cout << "Trying guess algorithm\n";
        while (true) {
            if (ga > 100) {
                std::cout << "Too many attempts on guess\n";
                ga = 1;
                break;
            }
            std::cout << "Guess #" << ga << "\n";
            board.calculate_guess();
            guess_ret = board.confirm_guess();
            if (guess_ret != 0) {
                std::cout << "Done with algorithm guess\n";
                break;
            }
            ga++;
        }
        std::cout << "Trying eliminate algorithm\n";
        gb = 1;
        while (true) {
            if (gb > 100) {
                std::cout << "Too many attempts on eliminate\n";
                gb = 1;
                break;
            }
            std::cout << "Elimination #" << gb << "\n";
            board.calculate_eliminate();
            elim_ret = board.confirm_eliminate();
            if (elim_ret != 0) {
                std::cout << "Done with algorithm eliminate\n";
                break;
            }
            gb++;
        }
        std::cout << "Trying crosshatch algorithm\n";
        gc = 1;
        while (true) {
            if (gc > 100) {
                std::cout << "Too many attempts on crosshatch\n";
                gc = 1;
                break;
            }
            std::cout << "Crosshatch #" << gc << "\n";
            board.calculate_crosshatch();
            cross_ret = board.confirm_crosshatch();
            //std::cout << "Returned " << cross_ret << "\n";
            if (cross_ret != 0) {
                std::cout << "Done with algorithm crosshatch\n";
                break;
            }
            gc++;
        }
        if (ga == 1 && gb == 1 && gc == 1) {
            std::cout << "Finished solving\n";
            retval = cross_ret - 1;
            break;
        }
    }
    board.saveBoard("result.json");
    return retval;
}
