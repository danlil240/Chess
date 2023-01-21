#include "chess_gui.hpp"
#include <QObject>

chess_gui::chess_gui(std::shared_ptr<MainWindow> w) : w_{w} {
    initBoard();
    initTeam(1, 0);
    initTeam(0, 1);
    chess_ = std::make_shared<board>();
}

void chess_gui::initBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            QPixmap pixmap;
            if (((i) % 2 > 0 and (j) % 2 > 0) or ((i) % 2 == 0 and (j) % 2 == 0)) {
                pixmap =
                        QPixmap(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                                "Shadow/1024px/square brown dark.png");
            } else {
                pixmap =
                        QPixmap(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                                "Shadow/1024px/square brown light.png");
            }
            squares_[i][j] = std::make_shared<gui_square>(
                        w_, Qt::WindowFlags(), pixmap,
                        QRect(i * 100 + 100, j * 100 + 50, 100, 100), i, j);

            connect(squares_[i][j].get(), &gui_square::clicked, this,
                    &chess_gui::buttonClicked);
        }
    }
}

void chess_gui::initTeam(int color, int up_down) {
    int j = up_down ? 6 : 1;
    int k = up_down ? 7 : 0;
    for (int i = 0; i < 8; i++) {
        makePiece(color, i, "pawn", squares_[i][j], i, j);
    }
    makePiece(color, 8, "rook", squares_[0][k], 0, k);
    makePiece(color, 9, "rook", squares_[7][k], 7, k);
    makePiece(color, 10, "knight", squares_[1][k], 1, k);
    makePiece(color, 11, "knight", squares_[6][k], 6, k);
    makePiece(color, 12, "bishop", squares_[2][k], 2, k);
    makePiece(color, 13, "bishop", squares_[5][k], 5, k);
    makePiece(color, 14, "queen", squares_[3][k], 3, k);
    makePiece(color, 15, "king", squares_[4][k], 4, k);
}

void chess_gui::makePiece(int color, int idx, std::string pic_name,
                          std::shared_ptr<gui_square> square, int x, int y) {
    std::string dir = ":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                      "Shadow/1024px/";
    std::string clr = color ? "w_" : "b_";
    std::shared_ptr<piece>(*team)[16] = color ? &w_team_ : &b_team_;
    (*team)[idx] = std::make_shared<piece>(
                w_, Qt::WindowFlags(),
                QPixmap(dir.append(clr + pic_name + ".png").c_str()), square->geometry(),
                x, y, color);
    square->piece_ = (*team)[idx];
    connect((*team)[idx].get(), &piece::clicked, this, &chess_gui::buttonClicked);
}

void chess_gui::move(int x, int y, int new_x, int new_y) {
    if (squares_[new_x][new_y]->piece_ != nullptr) {
        squares_[new_x][new_y]->piece_->hide();
    }
    squares_[x][y]->piece_->setGeometry(squares_[new_x][new_y]->geometry());
    squares_[x][y]->piece_->loc_x = new_x;
    squares_[x][y]->piece_->loc_y = new_y;
    squares_[new_x][new_y]->piece_ = squares_[x][y]->piece_;
    squares_[x][y]->piece_ = nullptr;
}

void chess_gui::buttonClicked(int x_, int y_) {
    if (squares_[x_][y_]->piece_ != nullptr and squre_pressed_ == nullptr) {
        /// First press
        squares_[x_][y_]->piece_->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        squares_[x_][y_]->piece_->setLineWidth(4);
        squre_pressed_ = squares_[x_][y_];
        clearSuggestions();
        available_moves.clear();
        chess_->checkAvailableMoves(x_, y_, available_moves);
        for (auto iter = available_moves.cbegin(); iter != available_moves.cend();
             iter++) {
            squares_[(*iter)[0]][(*iter)[1]]->setFrameStyle(QFrame::Box |
                                                            QFrame::Sunken);
            squares_[(*iter)[0]][(*iter)[1]]->setLineWidth(2);
        }
    } else if (squares_[x_][y_]->piece_ != nullptr and
               squre_pressed_ != nullptr) {
        if (squares_[x_][y_]->piece_ == squre_pressed_->piece_) {
            /// cancel first press
            squre_pressed_->piece_->setLineWidth(0);
            squre_pressed_ = nullptr;
            clearSuggestions();
        } else if (squre_pressed_->piece_->color ==
                   squares_[x_][y_]->piece_->color) {
            /// Sec press on piece same team
            squre_pressed_->piece_->setLineWidth(0);
            squre_pressed_ = squares_[x_][y_];
            squares_[x_][y_]->piece_->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            squre_pressed_->piece_->setLineWidth(4);
            clearSuggestions();
            available_moves.clear();
            chess_->checkAvailableMoves(x_, y_, available_moves);
            for (auto iter = available_moves.cbegin(); iter != available_moves.cend();
                 iter++) {
                squares_[(*iter)[0]][(*iter)[1]]->setFrameStyle(QFrame::Box |
                                                                QFrame::Sunken);
                squares_[(*iter)[0]][(*iter)[1]]->setLineWidth(2);
            }
        } else {
            /// Sec press on enemy
            if (checkAvailable(x_, y_)) {
                squre_pressed_->piece_->setLineWidth(0);
                old_places.clear();
                old_places.push_back(
                            std::array<int, 2>({squre_pressed_->loc_x, squre_pressed_->loc_y}));
                new_places.clear();
                new_places.push_back(std::array<int, 2>({x_, y_}));
                chess_->updateSquares(old_places, new_places);
                for (auto old_p = std::begin(old_places),
                     new_p = std::begin(new_places);
                     old_p != std::end(old_places); ++old_p, ++new_p) {
                    move((*old_p)[0], (*old_p)[1], (*new_p)[0], (*new_p)[1]);
                }
                squre_pressed_ = nullptr;
                clearSuggestions();
            }
        }

    } else if (squares_[x_][y_]->piece_ == nullptr and
               squre_pressed_ != nullptr) {
        /// Sec press on empty
        if (checkAvailable(x_, y_)) {
            squre_pressed_->piece_->setLineWidth(0);
            old_places.clear();
            old_places.push_back(
                        std::array<int, 2>({squre_pressed_->loc_x, squre_pressed_->loc_y}));
            new_places.clear();
            new_places.push_back(std::array<int, 2>({x_, y_}));
            chess_->updateSquares(old_places, new_places);
            for (auto old_p = std::begin(old_places), new_p = std::begin(new_places);
                 old_p != std::end(old_places); ++old_p, ++new_p) {
                move((*old_p)[0], (*old_p)[1], (*new_p)[0], (*new_p)[1]);
            }
            squre_pressed_ = nullptr;
            clearSuggestions();
        }

    } else {
    }
}

void chess_gui::clearSuggestions() {
    for (auto iter = available_moves.cbegin(); iter != available_moves.cend();
         iter++) {
        squares_[(*iter)[0]][(*iter)[1]]->setFrameStyle(QFrame::NoFrame |
                                                        QFrame::Sunken);
    }
}

bool chess_gui::checkAvailable(int x, int y) {
    for (auto iter = available_moves.cbegin(); iter != available_moves.cend();
         iter++) {
        if ((*iter)[0] == x and (*iter)[1] == y) {
            return true;
        }
    }
    return false;
}
