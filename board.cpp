#include "board.h"
#include "mainwindow.h"

board::board(std::shared_ptr<MainWindow> w)
{
	std::cout << "board born" << std::endl;

    board::init(w);
}

board::~board()
{
	std::cout << "board dead" << std::endl;
}

void board::init(std::shared_ptr<MainWindow> w)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            squares[i][j] = std::make_shared<ClickableLabel>(w);
            squares[i][j]->setGeometry(i*100+100, j*100+50, 100, 100);
            squares[i][j]->setSizeIncrement(squares[i][j]->width(),squares[i][j]->height());
            QPixmap pixmap;
            if (((i)%2>0 and (j)%2>0) or ((i)%2==0 and (j)%2==0)){
                pixmap.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                               "Shadow/1024px/square brown dark.png");
            }
            else{
               pixmap.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                               "Shadow/1024px/square brown light.png");
            }
            squares[i][j]->setPixmap(pixmap);
            squares[i][j]->setScaledContents(true);
        }
    }
}

void board::updateSquares(std::vector<int> from,std::vector<int> to){
	
    squares[from[0]][from[1]]->is_taken = false;
    squares[to[0]][to[1]]->is_taken = true;

}

bool  board::isTaken(std::vector<int> square) {
    return (squares[square[0]][square[1]]->is_taken);
}
