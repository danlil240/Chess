//#include "team.h"
#include <QApplication>

#include "chess_gui.h"


struct data_pass{
    bool pressed;
    std::vector<int> location;
    std::vector<int> new_location;
};

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  std::shared_ptr<MainWindow> main_window_ = std::make_shared<MainWindow>();
//  std::shared_ptr<board> board_ = std::make_shared<board>(main_window_);
//  std::shared_ptr<team> white_team_ =
//      std::make_shared<team>(white, board_, main_window_);
//  std::shared_ptr<team> black_team_ =
//      std::make_shared<team>(black, board_, main_window_);
  std::shared_ptr<chess_gui> gui= std::make_shared<chess_gui>(main_window_);
  main_window_->show();
  return a.exec();
}
