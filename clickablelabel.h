#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include "mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel {
  Q_OBJECT

public:
  explicit ClickableLabel(std::shared_ptr<MainWindow> parent = Q_NULLPTR,
                          Qt::WindowFlags f = Qt::WindowFlags(),QPixmap px=QPixmap(""),int x=0,int y=0,int w=0,int h=0);
  ~ClickableLabel();
  bool is_taken = false;


signals:
  void clicked();

protected:
  void mousePressEvent(QMouseEvent *event);
};

#endif // CLICKABLELABEL_H

class square : public ClickableLabel{
public:
    using ClickableLabel::ClickableLabel;
    std::shared_ptr<ClickableLabel> piece_ = nullptr;
};

class piece : public ClickableLabel{
public:
    using ClickableLabel::ClickableLabel;

};
