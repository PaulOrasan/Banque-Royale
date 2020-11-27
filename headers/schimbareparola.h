#ifndef SCHIMBAREPAROLA_H
#define SCHIMBAREPAROLA_H

#include <QDialog>

namespace Ui {
class schimbareParola;
}

class schimbareParola : public QDialog
{
    Q_OBJECT

public:
    explicit schimbareParola(QWidget *parent = nullptr);
    bool verificareSchimbari();
    ~schimbareParola();

private slots:
    void on_confirmaButton_clicked();

private:
    Ui::schimbareParola *ui;
};

#endif // SCHIMBAREPAROLA_H
