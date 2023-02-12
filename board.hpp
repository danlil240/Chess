#pragma once

#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <QMessageBox>


enum piece_type_description {
    king = 1,
    queen = 2,
    rook = 3,
    bishop = 4,
    knight = 5,
    pawn = 6
};

enum game_states{
    is_going,
    check,
    checkmate,
    draw
};

typedef std::array<std::array<int,2>,32> board_state;

enum team_color { black, white };

struct chess_piece {
    chess_piece(piece_type_description piece_type, team_color color,
                int dir)
        : piece_type(piece_type), color(color), dir(dir){};

    piece_type_description piece_type;
    team_color color;
    int dir;
    bool moved = false;
    bool alive_ = true;
    std::array<int, 2> location_ = {0, 0};
    std::vector<std::vector<int>> threats;
};

struct square {
    std::shared_ptr<chess_piece> piece;
    square(int x, int y) : x(x), y(y) { piece = nullptr; }
    int x, y;
    std::vector<std::shared_ptr<chess_piece>> threat_pieces;
    bool has_piece() { return piece != nullptr; }
};


struct gameState{
    game_states state =is_going;
    team_color team=white;
};


class board {

public:
    board();
    ~board();
    void updateSquares(std::vector<std::array<int, 2>> &old_places,
                       std::vector<std::array<int, 2>> &new_places,
                       bool formal = true,piece_type_description new_type = king);
    void updatePawn(std::array<int, 2> &location ,piece_type_description new_type = king);
    bool checkAvailableMoves(int x, int y,
                             std::vector<std::array<int, 2>> &available_moves);
    int black_up;
    gameState game_state;

private:

    board_state state_;
    board_state last_state_;
    std::array<std::shared_ptr<chess_piece>, 32> pieces_;
    void initTeam(std::array<std::shared_ptr<chess_piece>, 32>(*pieces),std::shared_ptr<square> (*squeres)[8][8]);
    void initSquares(std::shared_ptr<square> squares_[8][8]);
    void updateThreatensSquares(int x, int y);
    void updatePieces(std::array<std::array<int,2>,32> new_state);
    void checkAndMark(int x, int y, int dx, int dy,
                      std::shared_ptr<chess_piece> piece);
    void checkDirection(int x, int y, int dx, int dy,
                        std::shared_ptr<chess_piece> piece,
                        std::vector<std::array<int, 2>> &available_moves);
    void checkCastling(std::vector<std::array<int, 2>> &old_places,
                       std::vector<std::array<int, 2>> &new_places);
    bool notThreaten(std::shared_ptr<square> square, team_color piece_color);
    bool checkForMate(team_color color);
    std::shared_ptr<square> squares_[8][8];
    std::vector<std::array<int, 2>> knight_options_;
    std::vector<std::array<int, 2>> king_options_;
    int moves_cnt = 0;
    team_color turn = white;
};
