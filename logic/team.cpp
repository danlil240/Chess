#include "team.h"

team::team(team_color color,int up_down)
    : color_(color),up_down_(up_down) {

    std::vector<int> y;
     if (up_down) {
         y.push_back(0);
         y.push_back(1);
     }
     else{
         y.push_back(7);
         y.push_back(6);
     }

    for (int i = 0; i < 8; i++) {
      pieces[i] = std::make_shared<chess_piece>(pawn, color_, i, y[1]);
    }
    pieces[8] = std::make_shared<chess_piece>(rook, color_,
                                             0, y[0]);
    pieces[9] = std::make_shared<chess_piece>(rook, color_,
                                             7,  y[0]);
    pieces[10] = std::make_shared<chess_piece>(knight, color_,
                                              6,  y[0]);
    pieces[11] = std::make_shared<chess_piece>(knight, color_,
                                              1, y[0]);
    pieces[12] = std::make_shared<chess_piece>(bishop, color_,
                                              5,  y[0]);
    pieces[13] = std::make_shared<chess_piece>(bishop, color_,
                                              2,  y[0]);
    pieces[14] = std::make_shared<chess_piece>(king, color_,
                                              3,  y[0]);
    pieces[15] = std::make_shared<chess_piece>(queen, color_,
                                              4,  y[0]);
  }



team::~team() {}
