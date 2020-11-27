#ifndef PROFIL_H
#define PROFIL_H

#include <QDialog>

namespace Ui {
class profil;
}

class profil : public QDialog
{
    Q_OBJECT

public:
    explicit profil(QWidget *parent = nullptr);
    bool verificaSchimbari();
    bool verificaIntegritate();
    ~profil();

private slots:
    void on_numeCheckBox_stateChanged(int arg1);

    void on_prenumeCheckBox_stateChanged(int arg1);

    void on_CNPCheckBox_stateChanged(int arg1);

    void on_serieBuletinCheckBox_stateChanged(int arg1);

    void on_adresaCheckBox_stateChanged(int arg1);

    void on_dataNasteriiCheckBox_stateChanged(int arg1);

    void on_loculNasteriiCheckBox_stateChanged(int arg1);


    void on_confirmaButton_clicked();

    void on_schimbaParolaButton_clicked();

private:
    Ui::profil *ui;
};

#endif // PROFIL_H
