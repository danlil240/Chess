#include "chess_gui.h"
#include <QObject>
chess_gui::chess_gui(std::shared_ptr<MainWindow> w) {
    w_ = w;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            QPixmap pixmap;
            if (((i) % 2 > 0 and (j) % 2 > 0) or ((i) % 2 == 0 and (j) % 2 == 0)) {
                pixmap =
                        QPixmap(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                                "Shadow/1024px/square brown dark.png");
            } else {
                pixmap =
                        QPixmap(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                                "Shadow/1024px/square brown light.png");
            }
            squares_[i][j] = std::make_shared<square>(
                        w, Qt::WindowFlags(), pixmap,
                        QRect(i * 100 + 100, j * 100 + 50, 100, 100),i,j);

           connect(squares_[i][j].get(), &square::clicked,
                    this, &chess_gui::buttonClicked);
        }
    }
    initTeam(1,0);
    initTeam(0,1);

}

void chess_gui::initTeam(int color, int up_down) {
    int j=up_down ? 6 :  1;
    int k=up_down ? 7 :  0;
    for (int i = 0; i < 8; i++) {
        makePiece(color,i,"pawn",squares_[i][j],i,j);
    }
    makePiece(color,8,"rook",squares_[0][k],0,k);
    makePiece(color,9,"rook",squares_[7][k],7,k);
    makePiece(color,10,"knight",squares_[1][k],1,k);
    makePiece(color,11,"knight",squares_[6][k],6,k);
    makePiece(color,12,"bishop",squares_[2][k],2,k);
    makePiece(color,13,"bishop",squares_[5][k],5,k);
    makePiece(color,14,"queen",squares_[3][k],3,k);
    makePiece(color,15,"king",squares_[4][k],4,k);
}

void chess_gui::makePiece(int color,int idx,std::string pic_name,
                          std::shared_ptr<square> pos,int x,int y) {
    std::string dir = ":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                      "Shadow/1024px/";
    std::string clr = color ? "w_" :"b_";
    std::shared_ptr<piece> (*team)[16] = color ? &w_team_ :&b_team_;
    (*team)[idx] = std::make_shared<piece>(
                w_, Qt::WindowFlags(),
                QPixmap(dir.append(clr+pic_name+".png").c_str()),
                pos->geometry(),x,y);
    pos->piece_ = (*team)[idx];
}

void chess_gui::move(int x, int y, int new_x, int new_y){
    if (squares_[new_x][new_y]->piece_ != nullptr){
        squares_[new_x][new_y]->piece_->hide();
    }
    squares_[x][y]->piece_->setGeometry( squares_[new_x][new_y]->geometry());
    squares_[x][y]->piece_->loc_x=new_x;
    squares_[x][y]->piece_->loc_y=new_y;
    squares_[new_x][new_y]->piece_=squares_[x][y]->piece_;
    squares_[x][y]->piece_=nullptr;
}


void chess_gui::buttonClicked(int x_,int y_){
    std::cout << "x: " <<x_ << "\ty: " <<y_ << std::endl;
        int clicked=0;
        if (clicked==2){

        }

}

