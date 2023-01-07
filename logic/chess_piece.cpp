
#include "chess_piece.h"

chess_piece::chess_piece(piece_type_description piece_type, team_color color,
                         int x, int y,int dir)
    : piece_type(piece_type), color(color), dir(dir){

  std::cout << color << piece_type << " born" << std::endl;
}
chess_piece::~chess_piece() { std::cout << "dead" << std::endl; }

void chess_piece::executeMove(int new_location[2]) {
  location_[0] = new_location[0];
  location_[1] = new_location[1];
}

bool chess_piece::checkValidMove(int new_location[2]) {
  switch (this->piece_type) {
  case pawn:

    break;
  case rook:

    break;
  case bishop:

    break;
  case knight:

    break;
  case queen:

    break;
  case king:

    break;
  default:
    break;
  }
  std::cout << location_[1] - new_location[1] << std::endl;
  return (location_[1] - new_location[1] == dir);
  return 1;
}
