#include "clickablelabel.h"
#include <QMessageBox>
#include <string>


piece::piece(std::shared_ptr<MainWindow> parent, Qt::WindowFlags f,QPixmap px,QRect geo)
    : QLabel(parent.get()) {
    this->setPixmap(px);
    this->setScaledContents(true);
    this->setGeometry(geo);

    std::cout << "born" << std::endl;
}

piece::~piece() {}

void piece::mousePressEvent(QMouseEvent* event) {
    std::cout << this->x() << "\t" << this->y()  << "\tpressed" << std::endl;
    pressed=!pressed;
    emit clicked();
}



