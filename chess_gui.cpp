#include "chess_gui.h"

chess_gui::chess_gui(std::shared_ptr<MainWindow> w) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {

      QPixmap pixmap;
      if (((i) % 2 > 0 and (j) % 2 > 0) or ((i) % 2 == 0 and (j) % 2 == 0)) {
        pixmap.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                    "Shadow/1024px/square brown dark.png");
      } else {
        pixmap.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                    "Shadow/1024px/square brown light.png");
      }
      squares[i][j] = std::make_shared<square>(
          w, Qt::WindowFlags(), pixmap, i * 100 + 100, j * 100 + 50, 100, 100);
    }
  }

  for (int i = 0; i < 8; i++) {
    w_team[i] = std::make_shared<piece>(
       w, Qt::WindowFlags(), QPixmap(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
                "Shadow/1024px/w_pawn.png"),
        squares[i][1]->x(),squares[i][1]->y(),squares[i][1]->width(),squares[i][1]->height() );
  }
//  pieces[8] = std::make_shared<chess_piece>(rook, color_, board_,
//                                            std::vector({0, y[0]}), w);
//  pieces[9] = std::make_shared<chess_piece>(rook, color_, board_,
//                                            std::vector({7, y[0]}), w);
//  pieces[10] = std::make_shared<chess_piece>(knight, color_, board_,
//                                             std::vector({6, y[0]}), w);
//  pieces[11] = std::make_shared<chess_piece>(knight, color_, board_,
//                                             std::vector({1, y[0]}), w);
//  pieces[12] = std::make_shared<chess_piece>(bishop, color_, board_,
//                                             std::vector({5, y[0]}), w);
//  pieces[13] = std::make_shared<chess_piece>(bishop, color_, board_,
//                                             std::vector({2, y[0]}), w);
//  pieces[14] = std::make_shared<chess_piece>(king, color_, board_,
//                                             std::vector({3, y[0]}), w);
//  pieces[15] = std::make_shared<chess_piece>(queen, color_, board_,
//                                             std::vector({4, y[0]}), w);
}

//QPixmap chess_gui::pixmap(piece_type_description piece_type, team_color color) {
//  QPixmap px;
//  switch (color) {
//  case white:
//    switch (piece_type) {
//    case king:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/w_king.png");
//      break;
//    case queen:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/w_queen.png");
//      break;
//    case rook:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/w_rook.png");
//      break;
//    case bishop:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/w_bishop.png");
//      break;
//    case knight:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/w_knight.png");
//      break;
//    case pawn:
//      px.load();
//      break;
//    }

//    break;
//  case black:
//    switch (piece_type) {
//    case king:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/b_king.png");
//      break;
//    case queen:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/b_queen.png");
//      break;
//    case rook:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/b_rook.png");
//      break;
//    case bishop:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/b_bishop.png");
//      break;
//    case knight:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/b_knight.png");
//      break;
//    case pawn:
//      px.load(":/Resources/pics/JohnPablok Cburnett Chess set/PNGs/With "
//              "Shadow/1024px/b_pawn.png");
//      break;
//    }
//    break;
//  }
//  return px;
//}
