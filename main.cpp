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
    std::shared_ptr<MainWindow> main_window = std::make_shared<MainWindow>();
    std::shared_ptr<chess_gui> gui= std::make_shared<chess_gui>(main_window);
    main_window->show();
    return a.exec();
}
