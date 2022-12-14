#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "clickablelabel.h"
#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QtGui>
#include "mainwindow.h"



class board 
{
public:
    board(std::shared_ptr<MainWindow> w);
	~board();
	bool isTaken(std::vector<int> square);
	bool threaten;
    void updateSquares(std::vector<int> from,std::vector<int> to);
    std::shared_ptr<ClickableLabel> squares[8][8];

private:
    void init(std::shared_ptr<MainWindow> w);

};
