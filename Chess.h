#pragma once

#include "team.h"
#include <chrono>
#include <thread>

class chess{
public:
    chess();
    ~chess();

    int mainLoop();

    bool init();

    void firstPress(int x,int y);

    piece_type_description choosePiece();

    std::vector<int> choosePosition();

private:

};
