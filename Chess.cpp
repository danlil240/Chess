
#include "Chess.h"

chess::chess() {}
chess::~chess() {}
// team_color turn=white;
// int chess::mainLoop()
//{
//	init();
//	std::cout << "Welcome to Chess! Press enter to continue..." <<
// std::endl; 	std::cin.get();

//    std::shared_ptr<board> board1_= std::make_shared<board>();

//	while (true)
//	{
//		while (true)
//		{
//			std::cout << "Welcome to Chess! Press enter to
//continue..."
//<< std::endl; 			while (true)
//			{
//				std::vector<int> current_position =
// choosePosition();
//                if (board1_->isTaken(current_position)) {
//                    break;
//                }
//                else {
//                    std::cout << "There is no piece in that position" <<
//                    std::endl;
//                }
//			}
//			/*if (chsen_piece == null) return 0;*/
//			std::vector<int> desired_position = choosePosition();
//		}

////		turn = turn==white ? black : white;
//    }
//	return 0;
//}

// bool chess::init() {
//	std::shared_ptr<team> black_team= std::make_shared<team>(black);
//	std::shared_ptr<team> white_team= std::make_shared<team>(white);
//	return true;
// }

// piece_type_description chess::choosePiece() {
//	std::string piece;
//	std::cout << "Please pick a piece: " << std::endl;
//	while (1) {
//		std::getline(std::cin, piece);
//		if (piece == "king") {
//			return king;
//			break;
//		}
//		else if (piece == "queen") {
//			return queen;
//			break;
//		}
//		else if (piece == "rook") {
//			return rook;
//			break;
//		}
//		else if (piece == "knight") {
//			return knight;
//			break;
//		}
//		else if (piece == "bishop") {
//			return bishop;
//			break;
//		}
//		else if (piece == "pawn") {
//			return pawn;
//			break;
//		}
//		else if (piece == "q") {
//			return null;
//		}
//		else {
//			std::cout << "not a chess piece. try again or press q to
// exit!" << std::endl;
//		}
//	}
// }

// std::vector<int> chess::choosePosition() {
//	std::string piece;
//	int x, y;
//	while (1) {
//		try {
//			std::cout << "Please pick X: " << std::endl;
//			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//			std::cin >> x;
//			std::cout << "Please pick Y: " << std::endl;
//			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//			std::cin >> y;
//			if (x > 7 or y > 7 or x < 0 or y < 0) {
//				throw 3;
//			}
//			break;
//		}
//		catch (...) {
//			std::cout << "Numbers Only!" << std::endl;
//		}
//	}
//	std::cout << x << std::endl;
//	std::vector<int> a = { x,y };
//	return a;
// }
