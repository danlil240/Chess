#include "board.hpp"

board::board() {
    black_up = 1;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = std::make_shared<square>(i, j);
        }
    }
    initTeam(&black_team, black, black_up);
    initTeam(&white_team, white, !black_up);
}

board::~board() {}

void board::initTeam(std::array<std::shared_ptr<chess_piece>, 16>(*team),
                     team_color color, int up_down) {
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
        squares[i][y[1]]->piece = (*team)[i];
    }
    (*team)[8] = std::make_shared<chess_piece>(rook, color, 0, y[0], up_down);
    squares[0][y[0]]->piece = (*team)[8];
    (*team)[9] = std::make_shared<chess_piece>(rook, color, 7, y[0], up_down);
    squares[7][y[0]]->piece = (*team)[9];
    (*team)[10] = std::make_shared<chess_piece>(knight, color, 6, y[0], up_down);
    squares[6][y[0]]->piece = (*team)[10];
    (*team)[11] = std::make_shared<chess_piece>(knight, color, 1, y[0], up_down);
    squares[1][y[0]]->piece = (*team)[11];
    (*team)[12] = std::make_shared<chess_piece>(bishop, color, 5, y[0], up_down);
    squares[5][y[0]]->piece = (*team)[12];
    (*team)[13] = std::make_shared<chess_piece>(bishop, color, 2, y[0], up_down);
    squares[2][y[0]]->piece = (*team)[13];
    (*team)[14] = std::make_shared<chess_piece>(queen, color, 3, y[0], up_down);
    squares[3][y[0]]->piece = (*team)[14];
    (*team)[15] = std::make_shared<chess_piece>(king, color, 4, y[0], up_down);
    squares[4][y[0]]->piece = (*team)[15];
    for (auto piece = std::begin((*team)); piece != std::end((*team)); ++piece) {
        updateThreatensSquares(piece->get()->location_[0],
                piece->get()->location_[1]);
    }
}

void board::updateSquares(std::vector<std::array<int, 2>> &old_places,
                          std::vector<std::array<int, 2>> &new_places) {
    moves_cnt++;
    std::cout << "*************  Move number: " << moves_cnt << "  ************* " << std::endl;

    int new_x = new_places[0][0];
    int new_y = new_places[0][1];
    std::shared_ptr<square> new_square = squares[new_places[0][0]][new_places[0][1]];
    std::shared_ptr<square> old_square = squares[new_places[0][0]][new_places[0][1]];

    if (new_square->has_piece()) {
        if (new_square->piece->color != old_square->piece->color) { // attack
            std::shared_ptr<chess_piece> victim =
                    new_square->piece; // get the attacked piece
            for (auto i = std::begin(victim->threats); i < std::end(victim->threats);
                 i++) {
                auto vec = squares[(*i)[0]][(*i)[1]]->threat_pieces;
                vec.erase(std::remove(vec.begin(), vec.end(), victim),
                          vec.end()); // remove the attacked piece from all squares it threatens
            }
            new_square->piece->threats.clear();
        }
    }
    new_square->piece =
            first_square->piece; // move the chosen piece to the new position
    new_square->piece->location_ = {
        new_x, new_y}; // update the location of the piece
    new_square->piece->moved =
            true; // set moved attribute of the piece to true

    check_castling(old_places,new_places);
    auto threats = first_square->threat_pieces;
    first_square->piece = nullptr; // set the old position of the piece to null
    for (auto piece = std::begin(threats); piece != std::end(threats); ++piece) {
        updateThreatensSquares(
                    (*piece)->location_[0],
                (*piece)->location_[1]); // update the squares that the pieces threaten
    }
    updateThreatensSquares(
                new_x, new_y); // update the squares that the moved piece threatens
}

void board::check_castling(std::vector<std::array<int, 2>> &old_places,
                           std::vector<std::array<int, 2>> &new_places){
    int new_x = new_places[0][0]; // get x coordinate of new position
    int new_y = new_places[0][1]; // get y coordinate of new position
    if (first_square->piece->piece_type == king &&
            !king_moved_) { // check if the piece is a king and it has not moved yet
        king_moved_ = true;
        if (new_x - first_square->x == 2) { // check if king side castle move
            squares[first_square->x + 1][new_y]->piece =
                    squares[first_square->x + 3][new_y]
                    ->piece; // move the rook to the new position
            squares[first_square->x + 3][new_y]->piece->location_ = {
                first_square->x + 1, new_y}; // update the location of the rook
            squares[first_square->x + 3][new_y]->piece =
                    nullptr; // set the old position of the rook to null
            old_places.push_back(std::array<int, 2>(
                                     {first_square->x + 3,
                                      new_y})); // add old position of the rook to old_places vector
            new_places.push_back(std::array<int, 2>(
                                     {first_square->x + 1,
                                      new_y})); // add new position of the rook to new_places vector

            auto threats = squares[first_square->x + 3][new_y]->threat_pieces;
            for (auto piece = std::begin(threats); piece != std::end(threats);
                 ++piece) {
                updateThreatensSquares(
                            (*piece)->location_[0],
                        (*piece)
                        ->location_[1]); // update the squares that the pieces threaten
            }
            updateThreatensSquares(
                        first_square->x + 1,
                        new_y); // update the squares that the king and the rook threaten
        } else if (new_x - first_square->x ==
                   -2) { // check if queen side castle move
            squares[first_square->x - 1][new_y]->piece =
                    squares[first_square->x - 4][new_y]
                    ->piece; // move the rook to the new position
            squares[first_square->x - 4][new_y]->piece->location_ = {
                first_square->x - 1, new_y}; // update the location of the rook
            squares[first_square->x - 4][new_y]->piece =
                    nullptr; // set the old position of the rook to null
            old_places.push_back(std::array<int, 2>(
                                     {first_square->x - 4,
                                      new_y})); // add old position of the rook to old_places vector
            new_places.push_back(std::array<int, 2>(
                                     {first_square->x - 1,
                                      new_y})); // add new position of the rook to new_places vector
            auto threats = squares[first_square->x - 4][new_y]->threat_pieces;
            for (auto piece = std::begin(threats); piece != std::end(threats);
                 ++piece) {
                updateThreatensSquares(
                            (*piece)->location_[0],
                        (*piece)
                        ->location_[1]); // update the squares that the pieces threaten
            }
            updateThreatensSquares(
                        first_square->x + 1,
                        new_y); // update the squares that the king and the rook threaten
        }
    }
}

bool board::checkAvailableMoves(
        int x, int y, std::vector<std::array<int, 2>> &available_moves) {
    std::cout << "available moves for square: " << x << ", " << y << std::endl;
    if (squares[x][y]->has_piece()) {
        team_color color = (squares[x][y]->piece->color);
        std::shared_ptr<chess_piece> piece = squares[x][y]->piece;
        int dir = (squares[x][y]->piece->dir) * 2 - 1;
        first_square = squares[x][y];
        switch (piece->piece_type) {
        case pawn:
            std::cout << "pawn" << std::endl;
            if (!squares[x][y + dir]->has_piece()) {
                available_moves.push_back(std::array<int, 2>({x, y + dir}));
            }
            if (x < 7) {
                if (squares[x + 1][y + dir]->has_piece()) {
                    if (squares[x + 1][y + dir]->piece->color != color) {
                        available_moves.push_back(
                                    std::array<int, 2>({x + 1, y + dir})); // attack
                    }
                }
            }
            if (x > 0) {
                if (squares[x - 1][y + dir]->has_piece()) {
                    if (squares[x - 1][y + dir]->piece->color != color) {
                        available_moves.push_back(
                                    std::array<int, 2>({x - 1, y + dir})); // attack
                    }
                }
            }
            if (y - 2 * dir > 7 or y - 2 * dir < 0) {
                if (!squares[x][y + 2 * dir]->has_piece() &&
                        !squares[x][y + 1 * dir]->has_piece()) {
                    available_moves.push_back(
                                std::array<int, 2>({x, y + 2 * dir})); // first double step
                }
            }
            break;
        case rook:
            std::cout << "rook" << std::endl;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (!(i == 0 && j == 0) && (i * j == 0)) {
                        check_direction(x, y, i, j, piece, available_moves);
                    }
                }
            }
            break;
        case bishop:
            std::cout << "bishop" << std::endl;

            for (int i = -1; i <= 1; i += 2) {
                for (int j = -1; j <= 1; j += 2) {
                    check_direction(x, y, i, j, piece, available_moves);
                }
            }

            break;
        case knight:
            std::cout << "knight" << std::endl;

            knight_options_ = {{x + 2, y + 1}, {x - 2, y + 1}, {x + 2, y - 1},
                               {x - 2, y - 1}, {x + 1, y + 2}, {x - 1, y + 2},
                               {x + 1, y - 2}, {x - 1, y - 2}};
            for (auto it = std::begin(knight_options_);
                 it != std::end(knight_options_); ++it) {
                if ((*it)[0] >= 0 && (*it)[0] < 8 && (*it)[1] >= 0 && (*it)[1] < 8) {
                    if (squares[(*it)[0]][(*it)[1]]->piece) {
                        if ((squares[(*it)[0]][(*it)[1]]->piece->color != color)) {
                            available_moves.push_back(
                                        std::array<int, 2>({(*it)[0], (*it)[1]})); // attack
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

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0)
                        continue;
                    check_direction(x, y, i, j, piece, available_moves);
                }
            }
            break;
        case king:
            std::cout << "king" << std::endl;
            king_options_ = {{x + 1, y}, {x + 1, y + 1}, {x, y + 1}, {x - 1, y + 1},
                             {x - 1, y}, {x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1}};
            for (auto it = std::begin(king_options_); it != std::end(king_options_);
                 ++it) {
                if ((*it)[0] >= 0 && (*it)[0] < 8 && (*it)[1] >= 0 && (*it)[1] < 8) {
                    if (squares[(*it)[0]][(*it)[1]]->has_piece()) {
                        if (squares[(*it)[0]][(*it)[1]]->piece->color != color) {
                            available_moves.push_back(
                                        std::array<int, 2>({(*it)[0], (*it)[1]})); // king attack
                        } else {
                            continue;
                        }
                    }
                    available_moves.push_back(
                                std::array<int, 2>({(*it)[0], (*it)[1]})); // free move
                }
            }
            if (!king_moved_) { // castling
                if (black_up) {
                    if (!squares[x + 2][y]->has_piece() &&
                            !squares[x + 1][y]->has_piece() &&
                            !squares[x + 3][y]->piece->moved) {
                        available_moves.push_back(std::array<int, 2>({x + 2, y}));
                    }
                    if (!squares[x - 3][y]->has_piece() &&
                            !squares[x - 2][y]->has_piece() &&
                            !squares[x - 1][y]->has_piece() &&
                            !squares[x - 4][y]->piece->moved) {
                        available_moves.push_back(std::array<int, 2>({x - 2, y}));
                    }
                } else {
                    if (!squares[x - 2][y]->has_piece() &&
                            !squares[x - 1][y]->has_piece() &&
                            !squares[x - 3][y]->piece->moved) {
                        available_moves.push_back(std::array<int, 2>({x + 2, y}));
                    }
                    if (!squares[x + 3][y]->has_piece() &&
                            !squares[x + 2][y]->has_piece() &&
                            !squares[x + 1][y]->has_piece() &&
                            !squares[x + 4][y]->piece->moved) {
                        available_moves.push_back(std::array<int, 2>({x + 2, y}));
                    }
                }
            }
            break;
        default:
            break;
        }
    } else {
        std::cout << "not a piece" << std::endl;
    }
    for (auto available_move = std::begin(available_moves);
         available_move != std::end(available_moves); ++available_move) {
        auto i = (*available_move)[0];
        auto j = (*available_move)[1];
        std::cout << "x: " << i << "\ty: " << j << std::endl;
    }
    return 1;
}

void board::updateThreatensSquares(int x, int y) {

    int dir = (squares[x][y]->piece->dir) * 2 - 1;
    std::shared_ptr<chess_piece> piece = squares[x][y]->piece;

    //    team_color clr = piece->color;
    std::cout << "Threatens squares by square: " << x << ", " << y << std::endl;

    for (auto threaten_square = std::begin(piece->threats);
         threaten_square != std::end(piece->threats); ++threaten_square) {
        auto i = (*threaten_square)[0];
        auto j = (*threaten_square)[1];
        auto vec=squares[i][j]->threat_pieces;
        vec.erase(std::remove(vec.begin(), vec.end(), piece),
                  vec.end());
    }
    piece->threats.clear();
    switch (piece->piece_type) {

    case pawn:
        std::cout << "pawn" << std::endl;
        if (x < 7) {
            squares[x + 1][y + dir]->threat_pieces.push_back(piece);
            piece->threats.push_back({x + 1, y + dir});
        }
        if (x > 0) {
            squares[x - 1][y + dir]->threat_pieces.push_back(piece);
            piece->threats.push_back({x - 1, y + dir});
        }

        break;

    case rook:
        std::cout << "rook" << std::endl;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if ((i == 0 && j == 0) || (i != 0 && j != 0))
                    continue;
                check_and_mark(x, y, i, j, piece);
            }
        }
        break;

    case bishop:
        std::cout << "bishop" << std::endl;
        for (int i = -1; i <= 1; i += 2) {
            for (int j = -1; j <= 1; j += 2) {
                check_and_mark(x, y, i, j, piece);
            }
        }

        break;
    case knight:
        std::cout << "knight" << std::endl;

        knight_options_ = {{x + 2, y + 1}, {x - 2, y + 1}, {x + 2, y - 1},
                           {x - 2, y - 1}, {x + 1, y + 2}, {x - 1, y + 2},
                           {x + 1, y - 2}, {x - 1, y - 2}};
        for (auto it = std::begin(knight_options_); it != std::end(knight_options_);
             ++it) {
            if ((*it)[0] >= 0 && (*it)[0] < 8 && (*it)[1] >= 0 && (*it)[1] < 8) {
                squares[(*it)[0]][(*it)[1]]->threat_pieces.push_back(piece);
                piece->threats.push_back({(*it)[0], (*it)[1]});
            }
        }
        break;

    case queen:
        std::cout << "queen" << std::endl;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0)
                    continue;
                check_and_mark(x, y, i, j, piece);
            }
        }
        break;
    case king:
        std::cout << "king" << std::endl;
        king_options_ = {{x + 1, y}, {x + 1, y + 1}, {x, y + 1}, {x - 1, y + 1},
                         {x - 1, y}, {x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1}};
        for (auto it = std::begin(king_options_); it != std::end(king_options_);
             ++it) {
            if ((*it)[0] >= 0 && (*it)[0] < 8 && (*it)[1] >= 0 && (*it)[1] < 8) {
                squares[(*it)[0]][(*it)[1]]->threat_pieces.push_back(piece);
                piece->threats.push_back({(*it)[0], (*it)[1]});
            }
        }
        break;
    default:
        break;
    }
    for (auto threaten_square = std::begin(piece->threats);
         threaten_square != std::end(piece->threats); ++threaten_square) {
        auto x = (*threaten_square)[0];
        auto y = (*threaten_square)[1];
        std::cout << "x: " << x << "\ty: " << y << std::endl;
    }
}

void board::check_direction(int x, int y, int dx, int dy,
                            std::shared_ptr<chess_piece> piece,
                            std::vector<std::array<int, 2>> &available_moves) {
    int new_x = x + dx;
    int new_y = y + dy;
    while (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8) {
        if (squares[new_x][new_y]->has_piece()) {
            if (squares[new_x][new_y]->piece->color != piece->color) {
                available_moves.push_back(std::array<int, 2>({new_x, new_y}));
            }
            break;
        }
        available_moves.push_back(std::array<int, 2>({new_x, new_y}));
        new_x += dx;
        new_y += dy;
    }
}

void board::check_and_mark(int x, int y, int dx, int dy,
                           std::shared_ptr<chess_piece> piece) {
    int new_x = x;
    int new_y = y;
    while (true) {
        new_x += dx;
        new_y += dy;
        if (new_x < 0 || new_x >= 8 || new_y < 0 || new_y >= 8) {
            break;
        }
        squares[new_x][new_y]->threat_pieces.push_back(piece);
        piece->threats.push_back({new_x, new_y});
        if (squares[new_x][new_y]->has_piece()) {
            break;
        }
    }
}
