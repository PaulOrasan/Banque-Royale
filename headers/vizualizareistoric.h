#ifndef VIZUALIZAREISTORIC_H
#define VIZUALIZAREISTORIC_H

#include <QDialog>
#include "tranzactie.h"
namespace Ui {
class vizualizareIstoric;
}

class vizualizareIstoric : public QDialog
{
    Q_OBJECT

public:
    explicit vizualizareIstoric(QWidget *parent = nullptr);
    void displayTranzactie(tranzactie,int);
    ~vizualizareIstoric();

private slots:
    void on_confirmButton_clicked();

private:
    Ui::vizualizareIstoric *ui;
};

#endif // VIZUALIZAREISTORIC_H
