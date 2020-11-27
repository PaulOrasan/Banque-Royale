#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QDialog>

namespace Ui {
class menuPrincipal;
}

class menuPrincipal : public QDialog
{
    Q_OBJECT

public:
    explicit menuPrincipal(QWidget *parent = nullptr);
    ~menuPrincipal();

private slots:

    void on_profilButton_clicked();

    void on_statusBancarButton_clicked();

    void on_imprumutaButton_clicked();

    void on_transferaButton_clicked();

    void on_delogareButton_clicked();

    void on_aboutButton_clicked();

private:
    Ui::menuPrincipal *ui;
};

#endif // MENUPRINCIPAL_H
