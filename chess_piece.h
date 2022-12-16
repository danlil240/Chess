#pragma once

#include "board.h"
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
  chess_piece(piece_type_description piece_type, team_color color,
              std::shared_ptr<board> board_, std::vector<int> new_location);
  ~chess_piece();
  void executeMove(std::vector<int> new_location,
                   std::shared_ptr<board> board_);
  piece_type_description piece_type_;

private:
  team_color color_;
  bool checkMoveValid(std::vector<int> new_location);

  bool threaten_ = false;
  bool alive_ = true;
  std::vector<int> location_ = {0, 0};
  int dir_;

};
