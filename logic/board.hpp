#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

enum piece_type_description {
    king = 1,
    queen = 2,
    rook = 3,
    bishop = 4,
    knight = 5,
    pawn = 6
};

enum team_color { black, white };

struct chess_piece {
    chess_piece(piece_type_description piece_type, team_color color, int x, int y,
                int dir)
        : piece_type(piece_type), color(color), dir(dir), location_({x, y}){};

    piece_type_description piece_type;
    team_color color;
    int dir;
    bool moved = false;
    bool threaten_ = false;
    bool alive_ = true;
    std::array<int, 2> location_ = {0, 0};
    std::vector<std::vector<int>> threats;
};

struct square {
    std::shared_ptr<chess_piece> piece;
    bool isThreaten = false;
    square(int x, int y) : x(x), y(y) { piece = nullptr; }
    int x, y;
    std::vector<std::shared_ptr<chess_piece>> threat_pieces;
    bool has_piece(){
        return piece!=nullptr;
    }
};

class board {

public:
    board();
    ~board();
    void updateSquares(std::vector<std::array<int, 2>> &old_places,
                       std::vector<std::array<int, 2>> &new_places);
    bool checkAvailableMoves(int x, int y,
                             std::vector<std::array<int, 2>> &available_moves);
    int black_up;

private:
    std::array<std::shared_ptr<chess_piece>, 16> black_team;
    std::array<std::shared_ptr<chess_piece>, 16> white_team;
    void initTeam(std::array<std::shared_ptr<chess_piece>, 16>(*team),
                  team_color color, int up_down);
    void updateThreatensSquares(int x,int y);
    void check_and_mark(int x, int y, int dx, int dy,std::shared_ptr<chess_piece> piece);
    void check_direction(int x, int y, int dx, int dy, std::shared_ptr<chess_piece> piece, std::vector<std::array<int, 2>>& available_moves);
    void check_castling(std::vector<std::array<int, 2>> &old_places,
                        std::vector<std::array<int, 2>> &new_places);
    std::shared_ptr<square> squares[8][8];
    std::shared_ptr<square> first_square;
    std::vector<std::array<int, 2>> knight_options_;
    std::vector<std::array<int, 2>> king_options_;
    bool king_moved_ = false;
    int moves_cnt=0;

};
