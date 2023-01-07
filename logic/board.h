#pragma once


#include "chess_piece.h"

struct squere
{
    std::shared_ptr<chess_piece> piece;
    bool isThreaten=false;
    squere() {
        piece=nullptr;
    }
};
class board 
{

public:
    board();
	~board();
    void updateSquares(int new_x,int new_y);
    bool checkAvailableMoves(int x,int y,std::vector<int*> &available_moves);
private:
//    void init();
    std::shared_ptr<chess_piece> black_team[16];
    std::shared_ptr<chess_piece> white_team[16];
    void initTeam(std::shared_ptr<chess_piece>(*team)[16],team_color color,int up_down);
    std::shared_ptr<squere> squeres[8][8];
    std::shared_ptr<squere> chosen_squere;
};
