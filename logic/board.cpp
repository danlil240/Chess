#include "board.h"

board::board() {
  std::cout << "board born" << std::endl;
  int black_up = 1;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      squeres[i][j] = std::make_shared<squere>();
    }
  }
  initTeam(&black_team, black, black_up);
  initTeam(&white_team, white, !black_up);
}

board::~board() { std::cout << "board dead" << std::endl; }

void board::initTeam(std::shared_ptr<chess_piece> (*team)[16], team_color color,
                     int up_down) {
  std::vector<int> y;
  if (up_down) {
    y.push_back(0);
    y.push_back(1);
  } else {
    y.push_back(7);
    y.push_back(6);
  }
  for (int i = 0; i < 8; i++) {
    (*team)[i] = std::make_shared<chess_piece>(pawn, color, i, y[1],up_down);
    squeres[i][y[1]]->piece = (*team)[i];
  }
  (*team)[8] = std::make_shared<chess_piece>(rook, color, 0, y[0],up_down);
  squeres[0][y[0]]->piece = (*team)[8];
  (*team)[9] = std::make_shared<chess_piece>(rook, color, 7, y[0],up_down);
  squeres[7][y[0]]->piece = (*team)[9];
  (*team)[10] = std::make_shared<chess_piece>(knight, color, 6, y[0],up_down);
  squeres[6][y[0]]->piece = (*team)[10];
  (*team)[11] = std::make_shared<chess_piece>(knight, color, 1, y[0],up_down);
  squeres[1][y[0]]->piece = (*team)[11];
  (*team)[12] = std::make_shared<chess_piece>(bishop, color, 5, y[0],up_down);
  squeres[5][y[0]]->piece = (*team)[12];
  (*team)[13] = std::make_shared<chess_piece>(bishop, color, 2, y[0],up_down);
  squeres[2][y[0]]->piece = (*team)[13];
  (*team)[14] = std::make_shared<chess_piece>(king, color, 3, y[0],up_down);
  squeres[3][y[0]]->piece = (*team)[14];
  (*team)[15] = std::make_shared<chess_piece>(queen, color, 4, y[0],up_down);
  squeres[4][y[0]]->piece = (*team)[15];
}

void board::updateSquares(int new_x,int new_y) {
    squeres[new_x][new_y]->piece=chosen_squere->piece;
    chosen_squere->piece=nullptr;
}

bool board::checkAvailableMoves(int x, int y,
                                std::vector<int*> &available_moves) {
if (squeres[x][y]->piece){
    team_color color=(squeres[x][y]->piece->color);
    int dir = (squeres[x][y]->piece->dir)*2-1;
    chosen_squere=squeres[x][y];
    int tmp[2];
    switch (squeres[x][y]->piece->piece_type) {
    case pawn:

        std::cout << "pawn" << std::endl;
        if(!squeres[x][y+dir]->piece){
            tmp[0]=x;
            tmp[1]=y+dir;
        available_moves.push_back(tmp);
        }

      break;
    case rook:
        std::cout << "rook" << std::endl;

      break;
    case bishop:
        std::cout << "bishop" << std::endl;

      break;
    case knight:
        std::cout << "knight" << std::endl;

      break;
    case queen:
        std::cout << "queen" << std::endl;

      break;
    case king:
        std::cout << "king" << std::endl;

      break;
    default:
      break;
    }
}
else {
  std::cout << "not a piece" << std::endl;
}
  return 1;
}
