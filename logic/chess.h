#pragma once

#include "board.h"
#include <chrono>
#include <thread>

class chess{
public:
    chess();
    ~chess();

    int mainLoop();

    void firstPress(int x,int y,std::vector< std::array<int, 2>> &available_moves);

    void secondPress(int new_x,int new_y);

    piece_type_description choosePiece();

    std::vector<int> choosePosition();

    std::shared_ptr<board> board_;

private:

};
