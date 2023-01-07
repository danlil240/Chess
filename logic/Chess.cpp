
#include "chess.h"

chess::chess() {
      std::cout << "Welcome to Chess! Press enter to continue..." << std::endl;
     board_= std::make_shared<board>();
}
chess::~chess() {}

void chess::firstPress(int x,int y,std::vector<int*> &available_moves){
    board_->checkAvailableMoves(x,y,available_moves);
}

void chess::secondPress(int new_x,int new_y){
    board_->updateSquares(new_x,new_y);
}

 team_color turn=white;
 int chess::mainLoop()
{


    std::cin.get();



    while (true)
    {
        while (true)
        {
            std::cout << "Welcome to Chess! Press enter to" << std::endl; 			while (true)
            {

        }

        turn = turn==white ? black : white;
    }
    return 0;
}
 }

 piece_type_description chess::choosePiece() {
    std::string piece;
    std::cout << "Please pick a piece: " << std::endl;
    while (1) {
        std::getline(std::cin, piece);
        if (piece == "king") {
            return king;
            break;
        }
        else if (piece == "queen") {
            return queen;
            break;
        }
        else if (piece == "rook") {
            return rook;
            break;
        }
        else if (piece == "knight") {
            return knight;
            break;
        }
        else if (piece == "bishop") {
            return bishop;
            break;
        }
        else if (piece == "pawn") {
            return pawn;
            break;
        }
        else {
            std::cout << "not a chess piece. try again or press q to exit!" << std::endl;
        }
    }
 }
