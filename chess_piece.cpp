
#include "chess_piece.h"

chess_piece::chess_piece(piece_type_description piece_type, team_color color,
                         std::shared_ptr<board> board_,
                         std::vector<int> new_location)
    : piece_type_(piece_type), color_(color) {


  std::cout << color_ << piece_type << " born" << std::endl;
  dir_ = color_ * 2 - 1;
}
chess_piece::~chess_piece() { std::cout << "dead" << std::endl; }

void chess_piece::executeMove(std::vector<int> new_location,
                              std::shared_ptr<board> board_) {
  board_->updateSquares(location_, new_location);
  location_[0] = new_location[0];
  location_[1] = new_location[1];
}

bool chess_piece::checkMoveValid(std::vector<int> new_location) {

  std::cout << location_[1] - new_location[1] << std::endl;
  return (location_[1] - new_location[1] == dir_);
  return 1;
}
