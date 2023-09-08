#include "Optimizer.hpp"
#include "board.hpp"

Optimizer::Optimizer(std::shared_ptr<board> &chess,int moves_ahead): moves_ahead_(moves_ahead)
{
    chess_= chess;
}

void Optimizer::compute(board_state state){
    chess_->updatePieces(state);


    for (int move_cnt=0; move_cnt<moves_ahead_;move_cnt++){
        team_available_moves all_available_moves;
        for (int i=0;i<16;i++){
            piece_available_moves _piece_available_moves;
            chess_->checkAvailableMoves(state[i][0],state[i][1],_piece_available_moves);
            all_available_moves[i]=_piece_available_moves;
        }
    }
}
