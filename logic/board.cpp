#include "board.hpp"

board::board() {

    black_up = 1;
    initSquares(squares_);
    initTeam(&pieces_, &squares_);
    last_state_ = state_;

    //    std::memcpy(&last_state_,&state_,sizeof(state_));
}

board::~board() {}

void board::initSquares(std::shared_ptr<square> squares[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares[i][j] = std::make_shared<square>(i, j);
        }
    }
}

void board::initTeam(std::array<std::shared_ptr<chess_piece>, 32>(*pieces),
                     std::shared_ptr<square> (*squeres)[8][8]) {
    std::array<int, 2> y;
    for (int j = 0; j < 2; j++) {
        team_color color = j ? black : white;
        bool up_down;
        up_down = color == black ? black_up : !black_up;
        if (up_down) {
            y = {0, 1};
        } else {
            y = {7, 6};
        }
        int dir = up_down ? 1 : -1;
        int king_pos = black_up ? 3 : 4;
        int queen_pos = black_up ? 4 : 3;
        int first_idx = color ? 0 : 16;
        state_[0 + first_idx] = {king_pos, y[0]};
        state_[1 + first_idx] = {queen_pos, y[0]};
        state_[2 + first_idx] = {0, y[0]};
        state_[3 + first_idx] = {7, y[0]};
        state_[4 + first_idx] = {1, y[0]};
        state_[5 + first_idx] = {6, y[0]};
        state_[6 + first_idx] = {2, y[0]};
        state_[7 + first_idx] = {5, y[0]};
        for (int i = 0; i < 8; i++) {
            state_[i + 8 + first_idx] = {i, y[1]};
        }
        (*pieces)[0 + first_idx] = std::make_shared<chess_piece>(king, color, dir);
        (*pieces)[1 + first_idx] = std::make_shared<chess_piece>(queen, color, dir);
        (*pieces)[2 + first_idx] = std::make_shared<chess_piece>(rook, color, dir);
        (*pieces)[3 + first_idx] = std::make_shared<chess_piece>(rook, color, dir);
        (*pieces)[4 + first_idx] =
                std::make_shared<chess_piece>(knight, color, dir);
        (*pieces)[5 + first_idx] =
                std::make_shared<chess_piece>(knight, color, dir);
        (*pieces)[6 + first_idx] =
                std::make_shared<chess_piece>(bishop, color, dir);
        (*pieces)[7 + first_idx] =
                std::make_shared<chess_piece>(bishop, color, dir);
        for (int i = 8; i < 16; i++) {
            (*pieces)[i + first_idx] =
                    std::make_shared<chess_piece>(pawn, color, dir);
        }
    }
    updatePieces(state_);
}

void board::updatePieces(std::array<std::array<int, 2>, 32> new_state) {

    for (auto &row : squares_) {
        for (auto &square : row) {
            square->piece = nullptr;
            square->threat_pieces.clear();
        }
    }
    int i = 0;
    for (auto &piece : pieces_) {
        piece->threats.clear();
        piece->location_ = new_state[i];
        piece->alive_ = piece->location_[0] >= 0;
        if (piece->alive_) {
            squares_[new_state[i][0]][new_state[i][1]]->piece = piece;
        }

        i++;
    }
    for (auto &piece : pieces_) {
        updateThreatensSquares(piece->location_[0], piece->location_[1]);
    }
}

void board::updateSquares(std::vector<std::array<int, 2>> &old_places,
                          std::vector<std::array<int, 2>> &new_places,
                          bool formal) {
    int old_x = old_places[0][0];
    int old_y = old_places[0][1];
    int new_x = new_places[0][0];
    int new_y = new_places[0][1];
    std::shared_ptr<square> new_square = squares_[new_x][new_y];
    std::shared_ptr<square> old_square = squares_[old_x][old_y];
    auto main_piece = old_square->piece;
    if (new_square->has_piece()) {
        auto victim = new_square->piece;          // get the attacked piece
        if (victim->color != main_piece->color) { // attack
            for (auto i = std::begin(victim->threats); i < std::end(victim->threats);
                 i++) {
                auto *vec = &squares_[(*i)[0]][(*i)[1]]->threat_pieces;
                vec->erase(std::remove(vec->begin(), vec->end(), victim),
                           vec->end()); // remove the attacked piece from all squares it
                // threatens
            }
            victim->threats.clear();
            victim->alive_ = false;
            victim->location_ = {-1, -1};
            if (formal) {
                auto x = std::find(state_.begin(), state_.end(), old_places[0]);
                if (x != state_.end()) {
                    state_[x - state_.begin()] = {-1, -1};
                }
            }
        }
    }
    new_square->piece = main_piece; // move the chosen piece to the new position
    new_square->piece->location_ = {new_x,
                                    new_y}; // update the location of the piece

    checkCastling(old_places, new_places);
    new_square->piece->moved = true; // set moved attribute of the piece to true
    auto threats = old_square->threat_pieces;
    old_square->piece = nullptr; // set the old position of the piece to null
    for (auto piece = std::begin(threats); piece != std::end(threats); ++piece) {
        updateThreatensSquares(
                    (*piece)->location_[0],
                (*piece)->location_[1]); // update the squares that the pieces threaten
    }
    updateThreatensSquares(
                new_x, new_y); // update the squares that the moved piece threatens
    threats = new_square->threat_pieces;
    for (auto piece = std::begin(threats); piece != std::end(threats); ++piece) {
        updateThreatensSquares(
                    (*piece)->location_[0],
                (*piece)->location_[1]); // update the squares that the pieces threaten
    }
    if (formal) {
        moves_cnt++;
        std::string clr = turn == white ? "White" : "Black";
        std::cout << "*************   " << clr
                  << " turn.  Move number: " << moves_cnt << "  ************* "
                  << std::endl;
        for (int i = 0; i < old_places.size(); i++) {
            auto x = std::find(state_.begin(), state_.end(), old_places[i]);
            if (x != state_.end()) {
                state_[x - state_.begin()] = new_places[i];
            }
        }
        turn = turn == white ? black : white;
    }
}

void board::checkCastling(std::vector<std::array<int, 2>> &old_places,
                          std::vector<std::array<int, 2>> &new_places) {
    int new_x = new_places[0][0]; // get x coordinate of new position
    int new_y = new_places[0][1]; // get y coordinate of new position
    int old_x = old_places[0][0];
    int old_y = old_places[0][1];
    std::shared_ptr<square> new_square = squares_[new_x][new_y];
    std::shared_ptr<square> old_square = squares_[old_x][old_y];
    // check if the piece is a king and it has not moved yet
    if (old_square->piece->piece_type == king && !old_square->piece->moved) {
        int rook_x, new_rook_x;
        int r_rook;
        int l_rook;
        r_rook = black_up ? 4 : 3;
        l_rook = black_up ? -3 : -4;
        if (new_x - old_square->x == -2) { // king side castle move
            rook_x = old_square->x + l_rook;
            new_rook_x = old_square->x - 1;
        } else if (new_x - old_square->x == 2) { // queen side castle move
            rook_x = old_square->x + r_rook;
            new_rook_x = old_square->x + 1;
        } else
            return; // not a castle move
        squares_[new_rook_x][new_y]->piece = squares_[rook_x][new_y]->piece;
        squares_[new_rook_x][new_y]->piece->location_ = {new_rook_x, new_y};
        auto threats = squares_[new_rook_x][new_y]->threat_pieces;
        squares_[rook_x][new_y]->piece = nullptr;
        for (auto piece = std::begin(threats); piece != std::end(threats);
             ++piece) {
            updateThreatensSquares(
                        (*piece)->location_[0],
                    (*piece)
                    ->location_[1]); // update the squares that the pieces threaten
        }
        old_places.push_back({rook_x, new_y});
        new_places.push_back({new_rook_x, new_y});
        updateThreatensSquares(new_rook_x, new_y);
    }
}

bool board::checkAvailableMoves(
        int x, int y, std::vector<std::array<int, 2>> &available_moves) {
    //    std::cout << "available moves for square: " << x << ", " << y <<
    //    std::endl;
    available_moves.clear();
    if (squares_[x][y]->has_piece()) {
        std::shared_ptr<chess_piece> piece = squares_[x][y]->piece;
        team_color color = piece->color;
        if (color != turn)
            return 0;
        int dir = squares_[x][y]->piece->dir;
        auto king_idx = color ? 0 : 16;
        bool king_threaten = !notThreaten(squares_[pieces_[king_idx]->location_[0]]
                [pieces_[king_idx]->location_[1]],
                color);
        switch (piece->piece_type) {
        case pawn:
            //            std::cout << "pawn" << std::endl;
            if (!squares_[x][y + dir]->has_piece()) {
                available_moves.push_back(std::array<int, 2>({x, y + dir}));
            }
            if (x < 7) {
                if (squares_[x + 1][y + dir]->has_piece()) {
                    if (squares_[x + 1][y + dir]->piece->color != color) {
                        available_moves.push_back(
                                    std::array<int, 2>({x + 1, y + dir})); // attack
                    }
                }
            }
            if (x > 0) {
                if (squares_[x - 1][y + dir]->has_piece()) {
                    if (squares_[x - 1][y + dir]->piece->color != color) {
                        available_moves.push_back(
                                    std::array<int, 2>({x - 1, y + dir})); // attack
                    }
                }
            }
            if (y - 2 * dir > 7 or y - 2 * dir < 0) {
                if (!squares_[x][y + 2 * dir]->has_piece() &&
                        !squares_[x][y + 1 * dir]->has_piece()) {
                    available_moves.push_back(
                                std::array<int, 2>({x, y + 2 * dir})); // first double step
                }
            }
            break;
        case rook:
            //            std::cout << "rook" << std::endl;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (!(i == 0 && j == 0) && (i * j == 0)) {
                        checkDirection(x, y, i, j, piece, available_moves);
                    }
                }
            }
            break;
        case bishop:
            //            std::cout << "bishop" << std::endl;

            for (int i = -1; i <= 1; i += 2) {
                for (int j = -1; j <= 1; j += 2) {
                    checkDirection(x, y, i, j, piece, available_moves);
                }
            }

            break;
        case knight:
            //            std::cout << "knight" << std::endl;

            knight_options_ = {{x + 2, y + 1}, {x - 2, y + 1}, {x + 2, y - 1},
                               {x - 2, y - 1}, {x + 1, y + 2}, {x - 1, y + 2},
                               {x + 1, y - 2}, {x - 1, y - 2}};
            for (auto it = std::begin(knight_options_);
                 it != std::end(knight_options_); ++it) {
                if ((*it)[0] >= 0 && (*it)[0] < 8 && (*it)[1] >= 0 && (*it)[1] < 8) {
                    if (squares_[(*it)[0]][(*it)[1]]->piece) {
                        if ((squares_[(*it)[0]][(*it)[1]]->piece->color != color)) {
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
            //            std::cout << "queen" << std::endl;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0)
                        continue;
                    checkDirection(x, y, i, j, piece, available_moves);
                }
            }
            break;
        case king:
            //            std::cout << "king" << std::endl;
            king_options_ = {{x + 1, y}, {x + 1, y + 1}, {x, y + 1}, {x - 1, y + 1},
                             {x - 1, y}, {x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1}};
            for (auto it = std::begin(king_options_); it != std::end(king_options_);
                 ++it) {
                if ((*it)[0] >= 0 && (*it)[0] < 8 && (*it)[1] >= 0 && (*it)[1] < 8) {
                    if (squares_[(*it)[0]][(*it)[1]]->has_piece()) {
                        if (squares_[(*it)[0]][(*it)[1]]->piece->color != color) {
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
            if (!piece->moved) {
                int r_rook;
                int l_rook;
                r_rook = black_up ? 4 : 3;
                l_rook = black_up ? -3 : -4;

                bool r_clear = true, l_clear = true, r_non_threats = true,
                        l_non_threats = true;
                for (int i = 1; i < r_rook; i += 1) {
                    r_clear &= !squares_[x + i][y]->has_piece();
                }
                for (int i = -1; i > l_rook; i -= 1) {
                    l_clear &= !squares_[x + i][y]->has_piece();
                }
                for (int i = 0; i < r_rook; i += 1) {
                    r_non_threats &= notThreaten(squares_[x + i][y], piece->color);
                }
                for (int i = 0; i > l_rook; i -= 1) {
                    l_non_threats &= notThreaten(squares_[x + i][y], piece->color);
                }
                if (!squares_[x + r_rook][y]->piece->moved && r_clear &&
                        r_non_threats) {
                    available_moves.push_back(std::array<int, 2>({x + 2, y}));
                }
                if (!squares_[x + l_rook][y]->piece->moved && l_clear &&
                        l_non_threats) {
                    available_moves.push_back(std::array<int, 2>({x - 2, y}));
                }
            }
            break;
        default:
            break;
        }
        //        if (king_threaten) {
        std::vector<std::array<int, 2>> available_moves_temp;
        for (auto move : available_moves) {
            std::vector<std::array<int, 2>> old_p;
            std::vector<std::array<int, 2>> new_p;
            old_p = {{x, y}};
            new_p = {move};
            updateSquares(old_p, new_p, false);
            king_threaten = !notThreaten(squares_[pieces_[king_idx]->location_[0]]
                    [pieces_[king_idx]->location_[1]],
                    color);
            if (!king_threaten) {
                available_moves_temp.push_back(move);
            }
            updatePieces(state_);
        }
        available_moves = available_moves_temp;
        //        }
    } else {
        std::cout << "not a piece" << std::endl;
    }

    //    for (auto available_move = std::begin(available_moves);
    //         available_move != std::end(available_moves); ++available_move) {
    //        auto i = (*available_move)[0];
    //        auto j = (*available_move)[1];
    //        std::cout << "x: " << i << "\ty: " << j << std::endl;
    //    }
    return 1;
}

bool board::notThreaten(std::shared_ptr<square> square,
                        team_color piece_color) {
    for (auto &piece : square->threat_pieces)
        if (piece->color != piece_color)
            return false;
    return true;
}

void board::updateThreatensSquares(int x, int y) {

    int dir = squares_[x][y]->piece->dir;
    std::shared_ptr<chess_piece> piece = squares_[x][y]->piece;

        team_color clr = piece->color;
        std::cout << "Threatens squares by square: " << x << ", " << y <<  " by: ";
    //    std::endl;

    for (auto threaten_square = std::begin(piece->threats);
         threaten_square != std::end(piece->threats); ++threaten_square) {
        auto i = (*threaten_square)[0];
        auto j = (*threaten_square)[1];
        auto *vec = &(squares_[i][j]->threat_pieces);
        vec->erase(std::remove(vec->begin(), vec->end(), piece), vec->end());
    }
    piece->threats.clear();
    switch (piece->piece_type) {

    case pawn:
                std::cout << "pawn" << std::endl;
        if (x < 7) {
            squares_[x + 1][y + dir]->threat_pieces.push_back(piece);
            piece->threats.push_back({x + 1, y + dir});
        }
        if (x > 0) {
            squares_[x - 1][y + dir]->threat_pieces.push_back(piece);
            piece->threats.push_back({x - 1, y + dir});
        }

        break;

    case rook:
                std::cout << "rook" << std::endl;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if ((i == 0 && j == 0) || (i != 0 && j != 0))
                    continue;
                checkAndMark(x, y, i, j, piece);
            }
        }
        break;

    case bishop:
                std::cout << "bishop" << std::endl;
        for (int i = -1; i <= 1; i += 2) {
            for (int j = -1; j <= 1; j += 2) {
                checkAndMark(x, y, i, j, piece);
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
                squares_[(*it)[0]][(*it)[1]]->threat_pieces.push_back(piece);
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
                checkAndMark(x, y, i, j, piece);
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
                squares_[(*it)[0]][(*it)[1]]->threat_pieces.push_back(piece);
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

void board::checkDirection(int x, int y, int dx, int dy,
                           std::shared_ptr<chess_piece> piece,
                           std::vector<std::array<int, 2>> &available_moves) {
    int new_x = x + dx;
    int new_y = y + dy;
    while (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8) {
        if (squares_[new_x][new_y]->has_piece()) {
            if (squares_[new_x][new_y]->piece->color != piece->color) {
                available_moves.push_back(std::array<int, 2>({new_x, new_y}));
            }
            break;
        }
        available_moves.push_back(std::array<int, 2>({new_x, new_y}));
        new_x += dx;
        new_y += dy;
    }
}

void board::checkAndMark(int x, int y, int dx, int dy,
                         std::shared_ptr<chess_piece> piece) {
    int new_x = x;
    int new_y = y;
    while (true) {
        new_x += dx;
        new_y += dy;
        if (new_x < 0 || new_x >= 8 || new_y < 0 || new_y >= 8) {
            break;
        }
        squares_[new_x][new_y]->threat_pieces.push_back(piece);
        piece->threats.push_back({new_x, new_y});
        if (squares_[new_x][new_y]->has_piece()) {
            break;
        }
    }
}
