#ifndef clickablelabel_H
#define clickablelabel_H

#include "mainwindow.hpp"
#include <QLabel>
#include <QWidget>

#include <Qt>
#include <iostream>
#include <QThread>


class piece : public QLabel {
  Q_OBJECT

public:
  explicit piece(std::shared_ptr<MainWindow> parent = Q_NULLPTR,
                          Qt::WindowFlags f = Qt::WindowFlags(),QPixmap px=QPixmap(""),QRect geo=QRect(0,0,0,0),int x_=0,int y_=0,int color_=0);
  ~piece();
  bool pressed=false;
    int loc_x,loc_y;
    int color;
signals:
  void clicked(int X,int Y);

protected:
  void mousePressEvent(QMouseEvent *event);
};


class gui_square : public piece{
    Q_OBJECT
public:
    using piece::piece;
    ~gui_square(){
    }
    std::shared_ptr<piece> piece_ = nullptr;

private:
};

#endif // clickablelabel_H
