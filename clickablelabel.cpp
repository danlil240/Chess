#include "clickablelabel.h"
#include <QMessageBox>
#include <string>


ClickableLabel::ClickableLabel(std::shared_ptr<MainWindow> parent, Qt::WindowFlags f,QPixmap px,int x,int y,int w,int h)
    : QLabel(parent.get()) {
    this->setPixmap(px);
    this->setScaledContents(true);
    this->setGeometry(x,y,w,h);
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    //    QMessageBox msgBox;
    //    QString a=QString("%1  %2").arg( this->pos().x()).arg(this->pos().y());
    //    msgBox.setText(a);
    //    msgBox.setInformativeText("Do you want to save your changes?");
    //    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    //    msgBox.setDefaultButton(QMessageBox::Save);
    //    int ret = msgBox.exec();
    emit clicked();
}


