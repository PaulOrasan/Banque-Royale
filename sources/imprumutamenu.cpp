#include "headers/imprumutamenu.h"
#include "ui_imprumutamenu.h"
#include "headers/globals.h"
#include <QMessageBox>
#include <QPixmap>
imprumutaMenu::imprumutaMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imprumutaMenu)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    double rest=(double)10000-globals::userCurent.datorie;
    ui->remainingLineEdit->setText(QString::number(rest)); //valoarea pe care o mai poate imprumuta este diferenta dintre datorie
    ui->remainingLineEdit->setDisabled(true);              //si suma maxima care poate fi imprumutata
    ui->logo->setPixmap(globals::imagine->scaled(ui->logo->width(),ui->logo->height(),Qt::KeepAspectRatio));
    ui->imprumutaSpinBox->setRange(0,rest);
    QRegExp regInt("[0-9]{4,4}");
    ui->PINLineEdit->setValidator(new QRegExpValidator(regInt,this));
    ui->PINLineEdit->setMaxLength(4);
}

imprumutaMenu::~imprumutaMenu()
{
    delete ui;
}

void imprumutaMenu::on_confirmButton_clicked()
{
    if (ui->PINLineEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"État du prêt","Vous n’avez pas entré votre PIN");
        return;
    }else{
        if (globals::hasher.hash(ui->PINLineEdit->text())!=globals::userCurent.pin)
        {
            QMessageBox::critical(this,"État du prêt","Le code PIN incorrect");
            return;
        }
    }
    if (ui->imprumutaSpinBox->value()>0){
        double valoare=ui->imprumutaSpinBox->value();
        QString updateBalantaQuery="UPDATE `BALANTA` SET `valoare`=`valoare`+"+
                QString::number(valoare)+",`datorie`=`datorie`+"+QString::number(valoare)+" WHERE `id`="+
                QString::number(globals::userCurent.dbID);
        bool executed;
        globals::cfa->query(updateBalantaQuery,executed); //rulez un query pt actualizarea "balantei" (valoare si datorie)
        if (!executed){
            QMessageBox::critical(this,"État du prêt","Le prêt ne pouvait pas être atteint en raison de problèmes de communication avec le serveur de la Banque Royale");
            qDebug() << "trouble runnning update balanta query " << globals::cfa->getLastError();
            return;
        }
        globals::cfa->lastTranzactiiID=globals::cfa->getLastTranzactiiID()+1;
        QString insertTranzactieQuery="INSERT INTO `TRANZACTII`(`id`, `data/ora`, `tip`, `valoare`, `contFK`) VALUES ("+
                QString::number(globals::cfa->lastTranzactiiID)+",'"+
                QDateTime::currentDateTime().toString("yyyy.MM.dd.hh.mm.ss")+"','EMPRUNTER',"+
                QString::number(valoare)+","+QString::number(globals::userCurent.dbID)+")";
        globals::cfa->query(insertTranzactieQuery,executed); //rulez un query pt a salva o noua tranzactie de tip IMPRUMUT
        if (!executed){
            qDebug() << "trouble inserting new tranzactie " << globals::cfa->getLastError();
            return;
        }
        QMessageBox::information(this,"État du prêt","Emprunté avec succès "+QString::number(valoare)+" euro!");
        delete this;  //daca tranzactia s-a realizat cu succes inchid fereastra
    }else{
        QMessageBox::critical(this,"État du prêt","Choisissez une valeur");
    }
}
