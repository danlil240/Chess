#include "chess_gui.hpp"

chess_gui::chess_gui(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    newGame = new QAction(tr("N&ew Game"), this);
    newGame->setShortcuts(QKeySequence::New);
    connect(newGame, &QAction::triggered, this, &chess_gui::newGameSlot);

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newGame);
    fileMenu->addAction(exitAct);
    layout = new QGridLayout;

    newGameSlot();
}

void chess_gui::newGameSlot() {
    for (int i = 0; i < 16; i++) {
        w_team_[i].reset();
        b_team_[i].reset();
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            squares_[i][j].reset();
        }
    }
    chess_.reset();
    initBoard();
    chess_ = std::make_shared<board>();

    initTeam(1, !black_up_);
    initTeam(0, black_up_);
    turn=white;
     squre_pressed_ = nullptr;
}

void chess_gui::initBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            QPixmap pixmap;
            if ((i + j) % 2 == 0) {
                pixmap =
                        QPixmap(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                                "Shadow/1024px/square brown dark.png");
            } else {
                pixmap =
                        QPixmap(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                                "Shadow/1024px/square brown light.png");
            }
            squares_[i][j] = std::make_shared<gui_square>(
                        this, Qt::WindowFlags(), pixmap,
                        QRect(i * 100 + 100, j * 100 + 50, 100, 100), i, j);
            squares_[i][j]->show();
            connect(squares_[i][j].get(), &gui_square::clicked, this,
                    &chess_gui::buttonClicked);
        }
    }
}

void chess_gui::initTeam(int color, int up_down) {
    int j = up_down ? 1 : 6;
    int k = up_down ? 0 : 7;
    int king_pos = black_up_ ? 3 : 4;
    int queen_pos = black_up_ ? 4 : 3;
    for (int i = 0; i < 8; i++) {
        makePiece(color, i, "pawn", squares_[i][j], i, j);
    }
    makePiece(color, 8, "rook", squares_[0][k], 0, k);
    makePiece(color, 9, "rook", squares_[7][k], 7, k);
    makePiece(color, 10, "knight", squares_[1][k], 1, k);
    makePiece(color, 11, "knight", squares_[6][k], 6, k);
    makePiece(color, 12, "bishop", squares_[2][k], 2, k);
    makePiece(color, 13, "bishop", squares_[5][k], 5, k);
    makePiece(color, 14, "queen", squares_[queen_pos][k], queen_pos, k);
    makePiece(color, 15, "king", squares_[king_pos][k], king_pos, k);
}

void chess_gui::makePiece(int color, int idx, std::string pic_name,
                          std::shared_ptr<gui_square> square, int x, int y) {
    std::string dir = ":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                      "Shadow/1024px/";
    std::string clr = color ? "w_" : "b_";
    std::shared_ptr<piece>(*team)[16] = color ? &w_team_ : &b_team_;
    (*team)[idx] = std::make_shared<piece>(
                this, Qt::WindowFlags(),
                QPixmap(dir.append(clr + pic_name + ".png").c_str()), square->geometry(),
                x, y, color, pic_name);
    square->piece_ = (*team)[idx];
    (*team)[idx]->show();
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
    turn = turn == white ? black : white;
}

void chess_gui::buttonClicked(int x_, int y_) {
    if (squares_[x_][y_]->piece_ and !squre_pressed_) {
        /// First press
        if (squares_[x_][y_]->piece_->color == turn) {
            squares_[x_][y_]->piece_->setFrameStyle(QFrame::Panel | QFrame::Sunken);
            squares_[x_][y_]->piece_->setLineWidth(6);
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
        }
    } else if (squares_[x_][y_]->piece_ and squre_pressed_) {
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
        } else
            secPress(x_, y_); /// Sec press on enemy

    } else if (squares_[x_][y_]->piece_ == nullptr and squre_pressed_ != nullptr)
        secPress(x_, y_); /// Sec press on empty
}

void chess_gui::secPress(int x_, int y_) {
    if (checkAvailable(x_, y_)) {
        squre_pressed_->piece_->setLineWidth(0);
        old_places.clear();
        old_places.push_back({squre_pressed_->loc_x, squre_pressed_->loc_y});
        new_places.clear();
        new_places.push_back({x_, y_});

        chess_->updateSquares(old_places, new_places);
        for (auto old_p = std::begin(old_places), new_p = std::begin(new_places);
             old_p != std::end(old_places); ++old_p, ++new_p) {
            move((*old_p)[0], (*old_p)[1], (*new_p)[0], (*new_p)[1]);
        }
        if (old_places.size() > 1)
            turn = turn == white ? black : white;
        checkPawnAtEnd(x_, y_);
        squre_pressed_ = nullptr;
        clearSuggestions();
    }
}

void chess_gui::checkPawnAtEnd(int x_, int y_) {
    if (squares_[x_][y_]->piece_->name_ == "pawn") {
        if (y_ == 0 || y_ == 7) {
            piece_type_description piece_type;
            QMessageBox msgBox;
            msgBox.setText("Choose a chess piece:");
            QPushButton *queenButton =
                    msgBox.addButton("Queen", QMessageBox::ActionRole);
            QPushButton *rookButton =
                    msgBox.addButton("Rook", QMessageBox::ActionRole);
            QPushButton *bishopButton =
                    msgBox.addButton("Bishop", QMessageBox::ActionRole);
            QPushButton *knightButton =
                    msgBox.addButton("Knight", QMessageBox::ActionRole);

            msgBox.exec();
            int color = squares_[x_][y_]->piece_->color;
            QString d = ":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                        "Shadow/1024px/";
            QString clr = color ? "w_" : "b_";
            QString pic_name;
            if (msgBox.clickedButton() == queenButton) {
                piece_type = queen;
                pic_name = "queen";
                squares_[x_][y_]->piece_->name_ = "queen";
            } else if (msgBox.clickedButton() == rookButton) {
                piece_type = rook;
                pic_name = "rook";
                squares_[x_][y_]->piece_->name_ = "rook";
            } else if (msgBox.clickedButton() == bishopButton) {
                piece_type = bishop;
                pic_name = "bishop";
                squares_[x_][y_]->piece_->name_ = "bishop";
            } else if (msgBox.clickedButton() == knightButton) {
                piece_type = knight;
                pic_name = "knight";
                squares_[x_][y_]->piece_->name_ = "knight";
            }
            d.append(clr + pic_name + ".png");
            std::array<int, 2> a = {x_, y_};

            chess_->updatePawn(a, piece_type);
            std::cout << d.toStdString() << std::endl;
            squares_[x_][y_]->piece_->setPixmap(QPixmap(d));
            squares_[x_][y_]->piece_->show();
        }
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
    std::array<int, 2> new_place = {x, y};
    auto it =
            std::find(available_moves.begin(), available_moves.end(), new_place);
    return it != available_moves.end();
}
