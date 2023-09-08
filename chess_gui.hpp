#pragma once

#ifndef CHESS_GUI_H
#define CHESS_GUI_H

#include "board.hpp"
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include "./ui_mainwindow.h"
#include <QGridLayout>
//#include <QResizeEvent>
#include "optimizer.hpp"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class piece : public QLabel {
    Q_OBJECT

public:
    explicit piece(QWidget *parent = Q_NULLPTR,
                   Qt::WindowFlags f = Qt::WindowFlags(),
                   QPixmap px = QPixmap(""), QRect geo = QRect(0, 0, 0, 0),
                   int x_ = 0, int y_ = 0, int color_ = 0, std::string name = "")
        : QLabel(parent) {
        this->setPixmap(px);
        this->setScaledContents(true);
        this->setGeometry(geo);
//        this->setSizeIncrement(QSize(100,100));
//        this->setMaximumSize(QSize(120,120));
//       this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        loc_x = x_;
        loc_y = y_;
        color = color_;
        name_ = name;
    }

    bool pressed = false;
    int loc_x, loc_y;
    int color;
    std::string name_;
signals:
    void clicked(int X, int Y);

protected:
    void mousePressEvent(QMouseEvent *event) {
        pressed = !pressed;
        emit clicked(this->loc_x, this->loc_y);
    }
};

class gui_square : public piece {
    Q_OBJECT
public:
    using piece::piece;
    ~gui_square() {}
    std::shared_ptr<piece> piece_ = nullptr;

private:
};

class chess_gui : public QMainWindow {
    Q_OBJECT
public:
    chess_gui(QWidget *parent = nullptr);
    void move(int x, int y, int new_x, int new_y);
    std::vector<int> waitToPress();

private:
    std::shared_ptr<Optimizer> optimizer;
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QAction *exitAct;
    QAction *newGame;
    void newGameSlot();
    void initTeam(int color = 0, int up_down = 0);
    void initBoard();

    std::shared_ptr<board> chess_;
    QGridLayout *layout;
    QWidget *centralWidget ;

    void makePiece(int color, int idx, std::string pic_name,
                   std::shared_ptr<gui_square> pos, int x, int y);
    std::shared_ptr<gui_square> squares_[8][8];
    std::shared_ptr<piece> w_team_[16];
    std::shared_ptr<piece> b_team_[16];
    std::shared_ptr<gui_square> squre_pressed_ = nullptr;
    void buttonClicked(int x_, int y_);
    void checkPawnAtEnd(int x_, int y_);
    void secPress(int x_, int y_);
    void clearSuggestions();
//    void resizeEvent(QResizeEvent *event);
    std::vector<std::array<int, 2>> available_moves =
            std::vector<std::array<int, 2>>();
    std::vector<std::array<int, 2>> old_places =
            std::vector<std::array<int, 2>>();
    std::vector<std::array<int, 2>> new_places =
            std::vector<std::array<int, 2>>();
    team_color turn = white;
    bool black_up_;
    bool checkAvailable(int x, int y);

};

#endif // CHESS_GUI_H
