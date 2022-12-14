#pragma once

#ifndef CHESS_GUI_H
#define CHESS_GUI_H

#include "ClickableLabel.h"
#include "mainwindow.h"

// enum piece_type_description {
//   king = 1,
//   queen = 2,
//   rook = 3,
//   bishop = 4,
//   knight = 5,
//   pawn = 6
// };

// enum team_color { black, white };

class chess_gui {
public:
  chess_gui(std::shared_ptr<MainWindow> w);
  std::shared_ptr<square> squares[8][8];
  std::shared_ptr<piece> w_team[16];
  std::shared_ptr<piece> b_team[16];

private:

};

#endif // CHESS_GUI_H
