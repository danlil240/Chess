#include "clickablelabel.hpp"
#include <string>


piece::piece(std::shared_ptr<MainWindow> parent, Qt::WindowFlags f,QPixmap px,QRect geo,int x_,int y_,int color_,std::string name)
    : QLabel(parent.get()) {
    this->setPixmap(px);
    this->setScaledContents(true);
    this->setGeometry(geo);
    loc_x=x_;
    loc_y=y_;
    color=color_;
    name_=name;
}

piece::~piece() {}

void piece::mousePressEvent(QMouseEvent* event) {
    pressed=!pressed;
    emit clicked( this->loc_x, this->loc_y);
}



