#ifndef LOGINMENU_H
#define LOGINMENU_H

#include <QMainWindow>

namespace Ui {
class loginMenu;
}

class loginMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginMenu(QWidget *parent = nullptr);
    bool verificareFormularComplet();
    ~loginMenu();

private slots:
    void on_registerPushButton_clicked();

    void on_logInPushButton_clicked();

private:
    Ui::loginMenu *ui;
};

#endif // LOGINMENU_H
