#include "board.h"

board::board()
{
    std::cout << "board born" << std::endl;

    board::init();
}

board::~board()
{
    std::cout << "board dead" << std::endl;
}

void board::init()
{

}

void board::updateSquares(std::vector<int> from,std::vector<int> to){



}

bool  board::isTaken(std::vector<int> square) {
    return 1;
}
