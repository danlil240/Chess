#pragma once

#ifndef CHESS_GUI_H
#define CHESS_GUI_H

#include "ClickableLabel.h"
#include <QThread>


class chess_gui {
public:
  chess_gui(std::shared_ptr<MainWindow> w);
  void move(int x, int y, int new_x, int new_y);
  std::vector<int> waitToPress();

private:
  void initTeam(int color = 0, int up_down = 0);
  std::shared_ptr<MainWindow> w_;
  void makePiece(int color, int idx, std::string pic_name,
                 std::shared_ptr<square> pos,int x,int y);
  std::shared_ptr<square> squares_[8][8];
  std::shared_ptr<piece> w_team_[16];
  std::shared_ptr<piece> b_team_[16];
  bool pressed_=false;

};

#endif // CHESS_GUI_H
