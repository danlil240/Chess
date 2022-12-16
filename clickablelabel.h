#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include "mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <Qt>
#include <iostream>

class piece : public QLabel {
  Q_OBJECT

public:
  explicit piece(std::shared_ptr<MainWindow> parent = Q_NULLPTR,
                          Qt::WindowFlags f = Qt::WindowFlags(),QPixmap px=QPixmap(""),QRect geo=QRect(0,0,0,0));
  ~piece();
  bool pressed=false;
    int loc_x,loc_y;
signals:
  void clicked();

protected:
  void mousePressEvent(QMouseEvent *event);
};


class square : public piece{
public:
    using piece::piece;
    ~square(){
     std::cout << "piece died" << std::endl;
    }
    std::shared_ptr<piece> piece_ = nullptr;

private:
};

#endif // CLICKABLELABEL_H
