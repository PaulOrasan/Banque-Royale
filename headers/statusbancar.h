#ifndef STATUSBANCAR_H
#define STATUSBANCAR_H

#include <QDialog>

namespace Ui {
class statusBancar;
}

class statusBancar : public QDialog
{
    Q_OBJECT

public:
    explicit statusBancar(QWidget *parent = nullptr);
    double calculRataLunara(double datorie);
    ~statusBancar();

private slots:
    void on_pushButton_2_clicked();

    void on_setarePINButton_clicked();

private:
    Ui::statusBancar *ui;
};

#endif // STATUSBANCAR_H
