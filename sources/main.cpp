#include "headers/loginmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginMenu w;
    w.show();

    return a.exec();
}
