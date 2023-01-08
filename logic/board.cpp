#include "board.h"

board::board() {
  int black_up = 1;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      squeres[i][j] = std::make_shared<squere>();
    }
  }
  initTeam(&black_team, black, black_up);
  initTeam(&white_team, white, !black_up);
}

board::~board() {}

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
    (*team)[i] = std::make_shared<chess_piece>(pawn, color, i, y[1], up_down);
    squeres[i][y[1]]->piece = (*team)[i];
  }
  (*team)[8] = std::make_shared<chess_piece>(rook, color, 0, y[0], up_down);
  squeres[0][y[0]]->piece = (*team)[8];
  (*team)[9] = std::make_shared<chess_piece>(rook, color, 7, y[0], up_down);
  squeres[7][y[0]]->piece = (*team)[9];
  (*team)[10] = std::make_shared<chess_piece>(knight, color, 6, y[0], up_down);
  squeres[6][y[0]]->piece = (*team)[10];
  (*team)[11] = std::make_shared<chess_piece>(knight, color, 1, y[0], up_down);
  squeres[1][y[0]]->piece = (*team)[11];
  (*team)[12] = std::make_shared<chess_piece>(bishop, color, 5, y[0], up_down);
  squeres[5][y[0]]->piece = (*team)[12];
  (*team)[13] = std::make_shared<chess_piece>(bishop, color, 2, y[0], up_down);
  squeres[2][y[0]]->piece = (*team)[13];
  (*team)[14] = std::make_shared<chess_piece>(queen, color, 3, y[0], up_down);
  squeres[3][y[0]]->piece = (*team)[14];
  (*team)[15] = std::make_shared<chess_piece>(king, color, 4, y[0], up_down);
  squeres[4][y[0]]->piece = (*team)[15];
}

void board::updateSquares(int new_x, int new_y) {
  squeres[new_x][new_y]->piece = chosen_squere->piece;
  if (chosen_squere->piece->piece_type == king) {
    if (!king_moved_)
      {king_moved_ = true;}
  }
  chosen_squere->piece = nullptr;
}

bool board::checkAvailableMoves(
    int x, int y, std::vector<std::array<int, 2>> &available_moves) {
  if (squeres[x][y]->piece) {
    team_color color = (squeres[x][y]->piece->color);
    int dir = (squeres[x][y]->piece->dir) * 2 - 1;
    chosen_squere = squeres[x][y];
    switch (squeres[x][y]->piece->piece_type) {

    case pawn:
      std::cout << "pawn" << std::endl;
      if (!squeres[x][y + dir]->piece) {
        available_moves.push_back(std::array<int, 2>({x, y + dir}));
      }
      if (x < 7) {
        if (squeres[x + 1][y + dir]->piece) {
          if (squeres[x + 1][y + dir]->piece->color != color) {
            available_moves.push_back(std::array<int, 2>({x + 1, y + dir}));
          }
        }
      }
      if (x > 0) {
        if (squeres[x - 1][y + dir]->piece) {
          if (squeres[x - 1][y + dir]->piece->color != color) {
            available_moves.push_back(std::array<int, 2>({x - 1, y + dir}));
          }
        }
      }
      if (y - 2 * dir > 7 or y - 2 * dir < 0) {
        if (!squeres[x][y + 2 * dir]->piece and
            !squeres[x][y + 1 * dir]->piece) {
          available_moves.push_back(std::array<int, 2>({x, y + 2 * dir}));
        }
      }

      break;
    case rook:
      std::cout << "rook" << std::endl;
      for (int i = x + 1; i < 8; i++) {
        if (squeres[i][y]->piece) {
          if (!(squeres[i][y]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({i, y}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({i, y}));
      }
      for (int i = x - 1; i >= 0; i--) {
        if (squeres[i][y]->piece) {
          if (!(squeres[i][y]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({i, y}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({i, y}));
      }
      for (int i = y + 1; i < 8; i++) {
        if (squeres[x][i]->piece) {
          if (!(squeres[x][i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x, i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x, i}));
      }
      for (int i = y - 1; i >= 0; i--) {
        if (squeres[x][i]->piece) {
          if (!(squeres[x][i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x, i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x, i}));
      }
      break;
    case bishop:
      std::cout << "bishop" << std::endl;
      for (int i = 1; x + i < 8 and y + i < 8; i++) {
        if (squeres[x + i][y + i]->piece) {
          if (!(squeres[x + i][y + i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x + i, y + i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x + i, y + i}));
      }
      for (int i = 1; x + i < 8 and y - i >= 0; i++) {
        if (squeres[x + i][y - i]->piece) {
          if (!(squeres[x + i][y - i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x + i, y - i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x + i, y - i}));
      }
      for (int i = 1; x - i >= 0 and y + i < 8; i++) {
        if (squeres[x - i][y + i]->piece) {
          if (!(squeres[x - i][y + i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x - i, y + i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x - i, y + i}));
      }
      for (int i = 1; x - i >= 0 and y - i >= 0; i++) {
        if (squeres[x - i][y - i]->piece) {
          if (!(squeres[x - i][y - i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x - i, y - i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x - i, y - i}));
      }

      break;
    case knight:
      knight_options_ = {{x + 2, y + 1}, {x - 2, y + 1}, {x + 2, y - 1},
                         {x - 2, y - 1}, {x + 1, y + 2}, {x - 1, y + 2},
                         {x + 1, y - 2}, {x - 1, y - 2}};
      std::cout << "knight" << std::endl;
      for (auto it = std::begin(knight_options_);
           it != std::end(knight_options_); ++it) {
        if ((*it)[0] >= 0 && (*it)[0] < 8 && (*it)[1] >= 0 && (*it)[1] < 8) {
          if (squeres[(*it)[0]][(*it)[1]]->piece) {
            if (!(squeres[(*it)[0]][(*it)[1]]->piece->color == color)) {
              available_moves.push_back(
                  std::array<int, 2>({(*it)[0], (*it)[1]}));
            } else {
              continue;
            }
          }
          available_moves.push_back(std::array<int, 2>({(*it)[0], (*it)[1]}));
        }
      }

      break;
    case queen:
      std::cout << "queen" << std::endl;
      for (int i = x + 1; i < 8; i++) {
        if (squeres[i][y]->piece) {
          if (!(squeres[i][y]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({i, y}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({i, y}));
      }
      for (int i = x - 1; i >= 0; i--) {
        if (squeres[i][y]->piece) {
          if (!(squeres[i][y]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({i, y}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({i, y}));
      }
      for (int i = y + 1; i < 8; i++) {
        if (squeres[x][i]->piece) {
          if (!(squeres[x][i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x, i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x, i}));
      }
      for (int i = y - 1; i >= 0; i--) {
        if (squeres[x][i]->piece) {
          if (!(squeres[x][i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x, i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x, i}));
      }
      for (int i = 1; x + i < 8 and y + i < 8; i++) {
        if (squeres[x + i][y + i]->piece) {
          if (!(squeres[x + i][y + i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x + i, y + i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x + i, y + i}));
      }
      for (int i = 1; x + i < 8 and y - i >= 0; i++) {
        if (squeres[x + i][y - i]->piece) {
          if (!(squeres[x + i][y - i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x + i, y - i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x + i, y - i}));
      }
      for (int i = 1; x - i >= 0 and y + i < 8; i++) {
        if (squeres[x - i][y + i]->piece) {
          if (!(squeres[x - i][y + i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x - i, y + i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x - i, y + i}));
      }
      for (int i = 1; x - i >= 0 and y - i >= 0; i++) {
        if (squeres[x - i][y - i]->piece) {
          if (!(squeres[x - i][y - i]->piece->color == color)) {
            available_moves.push_back(std::array<int, 2>({x - i, y - i}));
          }
          break;
        }
        available_moves.push_back(std::array<int, 2>({x - i, y - i}));
      }
      break;
    case king:

      std::cout << "king" << std::endl;
      king_options_ = {{x + 1, y}, {x + 1, y + 1}, {x, y + 1}, {x - 1, y + 1},
                       {x - 1, y}, {x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1}};
      for (auto it = std::begin(king_options_); it != std::end(king_options_);
           ++it) {
        if ((*it)[0] >= 0 && (*it)[0] < 8 && (*it)[1] >= 0 && (*it)[1] < 8) {
          if (squeres[(*it)[0]][(*it)[1]]->piece) {
            if (!(squeres[(*it)[0]][(*it)[1]]->piece->color == color)) {
              available_moves.push_back(
                  std::array<int, 2>({(*it)[0], (*it)[1]}));
            } else {
              continue;
            }
          }
          available_moves.push_back(std::array<int, 2>({(*it)[0], (*it)[1]}));
        }
      }
      if (!king_moved_) { // castling
        if (!squeres[x + 2][y]->piece and !squeres[x + 1][y]->piece) {
          available_moves.push_back(std::array<int, 2>({x + 2, y}));
        }
        if (!squeres[x - 3][y]->piece and !squeres[x - 2][y]->piece and
            !squeres[x - 1][y]->piece) {
          available_moves.push_back(std::array<int, 2>({x - 2, y}));
        }
      }
      break;
    default:
      break;
    }
  } else {
    std::cout << "not a piece" << std::endl;
  }
  return 1;
}
