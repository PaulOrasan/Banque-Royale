#include "headers/statusbancar.h"
#include "ui_statusbancar.h"
#include "headers/globals.h"
#include "headers/vizualizareistoric.h"
#include "headers/setarepin.h"
statusBancar::statusBancar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statusBancar)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->logo->setPixmap(globals::imagine->scaled(ui->logo->width(),ui->logo->height(),Qt::KeepAspectRatio));
    globals::userCurent.descarcaUser();
    QString codBancar=globals::userCurent.codBancar;
    codBancar.insert(4,'-');
    codBancar.insert(9,'-');
    codBancar.insert(14,'-');
    QStringList cod=codBancar.split('-');
    ui->codPrimaLineEdit->setText(cod.at(0));
    ui->codPrimaLineEdit->setReadOnly(true);
    ui->codADouaLineEdit->setText(cod.at(1));
    ui->codADouaLineEdit->setReadOnly(true);
    ui->codATreiaLineEdit->setText(cod.at(2));
    ui->codATreiaLineEdit->setReadOnly(true);
    ui->codAPatraLineEdit->setText(cod.at(3));
    ui->codAPatraLineEdit->setReadOnly(true);
    globals::userCurent.descarcaUser();
    ui->valoareLineEdit->setText(QString::number(globals::userCurent.valoare));
    ui->datorieLineEdit->setText(QString::number(globals::userCurent.datorie));
    ui->rataLunaraLineEdit->setText(QString::number(statusBancar::calculRataLunara(globals::userCurent.datorie)));
    ui->valoareLineEdit->setReadOnly(true);
    ui->datorieLineEdit->setReadOnly(true);
}
double statusBancar::calculRataLunara(double datorie)
{
    int dobanda=8; //procent dobanda
    return ((double)(100+dobanda)*datorie/(double)100)/(double)12;
}
statusBancar::~statusBancar()
{
    delete ui;
}

void statusBancar::on_pushButton_2_clicked()
{
    vizualizareIstoric *vizualizare=new vizualizareIstoric;
    vizualizare->setModal(true);
    vizualizare->exec();
}

void statusBancar::on_setarePINButton_clicked()
{
    setarePIN *pin=new setarePIN;
    pin->setModal(true);
    pin->exec();
}
