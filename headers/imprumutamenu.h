#ifndef IMPRUMUTAMENU_H
#define IMPRUMUTAMENU_H

#include <QDialog>

namespace Ui {
class imprumutaMenu;
}

class imprumutaMenu : public QDialog
{
    Q_OBJECT

public:
    explicit imprumutaMenu(QWidget *parent = nullptr);
    ~imprumutaMenu();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::imprumutaMenu *ui;
};

#endif // IMPRUMUTAMENU_H
