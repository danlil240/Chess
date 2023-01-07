#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>

enum piece_type_description {
  king = 1,
  queen = 2,
  rook = 3,
  bishop = 4,
  knight = 5,
  pawn = 6
};

enum team_color { black, white };

class chess_piece {

public:
     chess_piece(piece_type_description piece_type, team_color color,int x ,int y,int dir);
    ~chess_piece();
     void executeMove(int new_location[2]);
    piece_type_description piece_type;
    team_color color;
    int dir;
private:

    bool checkValidMove(int new_location[2]);

    bool threaten_ = false;
    bool alive_ = true;
    int location_[2] = {0, 0};


};
