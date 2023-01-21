#pragma once

#ifndef CHESS_GUI_H
#define CHESS_GUI_H

#include "board.hpp"
#include "ClickableLabel.hpp"

class chess_gui : public QWidget {
  Q_OBJECT
public:
  chess_gui(std::shared_ptr<MainWindow> w);
  void move(int x, int y, int new_x, int new_y);
  std::vector<int> waitToPress();

private:
  void initTeam(int color = 0, int up_down = 0);
  void initBoard();
  std::shared_ptr<MainWindow> w_;
  std::shared_ptr<board> chess_;
  void makePiece(int color, int idx, std::string pic_name,
                 std::shared_ptr<gui_square> pos, int x, int y);
  std::shared_ptr<gui_square> squares_[8][8];
  std::shared_ptr<piece> w_team_[16];
  std::shared_ptr<piece> b_team_[16];
  std::shared_ptr<gui_square> squre_pressed_ = nullptr;
  void buttonClicked(int x_, int y_);
  void clearSuggestions();

  std::vector< std::array<int, 2>> available_moves=std::vector< std::array<int, 2>>();
  std::vector< std::array<int, 2>> old_places=std::vector< std::array<int, 2>>();
  std::vector< std::array<int, 2>> new_places=std::vector< std::array<int, 2>>();

bool checkAvailable(int x, int y);
};

#endif // CHESS_GUI_H
