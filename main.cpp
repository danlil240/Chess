//#include "team.h"
#include <QApplication>
#include "chess_gui.hpp"


struct data_pass{
    bool pressed;
    std::vector<int> location;
    std::vector<int> new_location;
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::shared_ptr<chess_gui> main_window = std::make_shared<chess_gui>();
    main_window->show();
    return a.exec();
}
