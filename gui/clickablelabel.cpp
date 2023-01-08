#include "clickablelabel.h"
#include <QMessageBox>
#include <string>


piece::piece(std::shared_ptr<MainWindow> parent, Qt::WindowFlags f,QPixmap px,QRect geo,int x_,int y_,int color_)
    : QLabel(parent.get()) {
    this->setPixmap(px);
    this->setScaledContents(true);
    this->setGeometry(geo);
    this->loc_x=x_;
    this->loc_y=y_;
    this->color=color_;
}

piece::~piece() {}

void piece::mousePressEvent(QMouseEvent* event) {
    std::cout << this->x() << "\t" << this->y()  << "\tpressed" << std::endl;
    pressed=!pressed;
    emit clicked( this->loc_x, this->loc_y);
}



