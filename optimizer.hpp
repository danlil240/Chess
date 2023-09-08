#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "board.hpp"




class Optimizer
{
public:
    Optimizer(std::shared_ptr<board> &chess,int moves_ahead);
    void compute(board_state state);

private:
    std::shared_ptr<board> chess_;
    int moves_ahead_;
};

#endif // OPTIMIZER_H
