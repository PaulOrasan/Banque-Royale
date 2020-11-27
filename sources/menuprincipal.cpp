#include "headers/menuprincipal.h"
#include "ui_menuprincipal.h"
#include "headers/profil.h"
#include "headers/statusbancar.h"
#include "headers/imprumutamenu.h"
#include "headers/transfermenu.h"
#include "headers/despre.h"
#include "headers/globals.h"
menuPrincipal::menuPrincipal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuPrincipal)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->logo->setPixmap(globals::imagine->scaled(ui->logo->width(),ui->logo->height(),Qt::KeepAspectRatio));
}

menuPrincipal::~menuPrincipal()
{
    delete ui;
}


void menuPrincipal::on_profilButton_clicked()
{
    profil *formularProfil=new profil;
    formularProfil->setModal(true);
    formularProfil->exec();
}

void menuPrincipal::on_statusBancarButton_clicked()
{
    statusBancar *status=new statusBancar;
    status->setModal(true);
    status->exec();
}

void menuPrincipal::on_imprumutaButton_clicked()
{
    imprumutaMenu *menu=new imprumutaMenu;
    menu->setModal(true);
    menu->exec();
}

void menuPrincipal::on_transferaButton_clicked()
{
    transferMenu *menu=new transferMenu;
    menu->setModal(true);
    menu->exec();
}

void menuPrincipal::on_delogareButton_clicked()
{
    delete this;
}

void menuPrincipal::on_aboutButton_clicked()
{
    despre *noi=new despre;
    noi->setModal(true);
    noi->exec();
}
