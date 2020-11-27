#include "headers/profil.h"
#include "ui_profil.h"
#include "headers/globals.h"
#include "headers/schimbareparola.h"
#include <QMessageBox>
#include "headers/registerdialog.h"
profil::profil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profil)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    qDebug() << globals::userCurent.serieBuletin;
    //setare politica de acceptare a caracterelor
    QRegExp regInt("[0-9]{13,13}");
    ui->CNPLineEdit->setValidator(new QRegExpValidator(regInt,this));
    ui->CNPLineEdit->setMaxLength(13);
    ui->serieBuletinCodLineEdit->setValidator(new QIntValidator);
    ui->serieBuletinCodLineEdit->setMaxLength(6);
    QRegExp regChar("[A-Za-z]{1,2}");
    ui->serieBuletinJudLineEdit->setValidator(new QRegExpValidator(regChar,this));
    QRegExp regNume("[A-Za-z -]{30,30}");
    ui->nameLineEdit->setValidator(new QRegExpValidator(regNume,this));
    ui->prenumeLineEdit->setValidator(new QRegExpValidator(regNume,this));
    //setare stare intiala formular
    ui->nameLineEdit->setText(globals::userCurent.nume);
    ui->nameLineEdit->setDisabled(true);
    ui->prenumeLineEdit->setText(globals::userCurent.prenume);
    ui->prenumeLineEdit->setDisabled(true);
    ui->CNPLineEdit->setText(globals::userCurent.CNP);
    ui->CNPLineEdit->setDisabled(true);
    ui->adresaLineEdit->setText(globals::userCurent.adresa);
    ui->adresaLineEdit->setDisabled(true);
    ui->dataNasteriiEdit->setDate(globals::userCurent.dataNasterii);
    ui->dataNasteriiEdit->setDisabled(true);
    ui->loculNasteriiLineEdit->setText(globals::userCurent.loculNasterii);
    ui->loculNasteriiLineEdit->setDisabled(true);
    QStringList serieBuletin=globals::userCurent.serieBuletin.split(' ');
    ui->serieBuletinJudLineEdit->setText(serieBuletin.at(0));
    ui->serieBuletinJudLineEdit->setDisabled(true);
    ui->serieBuletinCodLineEdit->setText(serieBuletin.at(1));
    ui->serieBuletinCodLineEdit->setDisabled(true);
}

profil::~profil()
{
    delete ui;
}

void profil::on_numeCheckBox_stateChanged(int arg1)
{
    //daca casuta editeaza este bifata, permite editarea, altfel nu si afiseaza valoarea existenta
    if (arg1==0)
    {
        ui->nameLineEdit->setText(globals::userCurent.nume);
        ui->nameLineEdit->setDisabled(true);
    }else {
        ui->nameLineEdit->setEnabled(true);
    }
}

void profil::on_prenumeCheckBox_stateChanged(int arg1)
{
    if (arg1==0)
    {
        ui->prenumeLineEdit->setText(globals::userCurent.prenume);
        ui->prenumeLineEdit->setDisabled(true);
    }else {
        ui->prenumeLineEdit->setEnabled(true);
    }
}

void profil::on_CNPCheckBox_stateChanged(int arg1)
{
    if (arg1==0)
    {
        ui->CNPLineEdit->setText(globals::userCurent.CNP);
        ui->CNPLineEdit->setDisabled(true);
    }else {
        ui->CNPLineEdit->setEnabled(true);
    }
}

void profil::on_serieBuletinCheckBox_stateChanged(int arg1)
{
    QStringList serieBuletin=globals::userCurent.serieBuletin.split(' ');
    if (arg1==0)
    {
        ui->serieBuletinJudLineEdit->setText(serieBuletin.at(0));
        ui->serieBuletinJudLineEdit->setDisabled(true);
        ui->serieBuletinCodLineEdit->setText(serieBuletin.at(1));
        ui->serieBuletinCodLineEdit->setDisabled(true);
    }else{
        ui->serieBuletinCodLineEdit->setEnabled(true);
        ui->serieBuletinJudLineEdit->setEnabled(true);
    }
}

void profil::on_adresaCheckBox_stateChanged(int arg1)
{
    if (arg1==0)
    {
        ui->adresaLineEdit->setText(globals::userCurent.adresa);
        ui->adresaLineEdit->setDisabled(true);
    }else{
        ui->adresaLineEdit->setEnabled(true);
    }
}

void profil::on_dataNasteriiCheckBox_stateChanged(int arg1)
{
    if (arg1==0)
    {
        ui->dataNasteriiEdit->setDate(globals::userCurent.dataNasterii);
        ui->dataNasteriiEdit->setDisabled(true);
    }else{
        ui->dataNasteriiEdit->setEnabled(true);
    }
}

void profil::on_loculNasteriiCheckBox_stateChanged(int arg1)
{
    if (arg1==0)
    {
        ui->loculNasteriiLineEdit->setText(globals::userCurent.loculNasterii);
        ui->loculNasteriiLineEdit->setDisabled(true);
    }else{
        ui->loculNasteriiLineEdit->setEnabled(true);
    }
}
bool profil::verificaSchimbari()
{
    bool verificator=false;
    verificator|=!(ui->nameLineEdit->text()==globals::userCurent.nume);
    verificator|=!(ui->prenumeLineEdit->text()==globals::userCurent.prenume);
    verificator|=!(ui->CNPLineEdit->text()==globals::userCurent.CNP);
    verificator|=!(ui->adresaLineEdit->text()==globals::userCurent.adresa);
    verificator|=!(ui->dataNasteriiEdit->date()==globals::userCurent.dataNasterii);
    verificator|=!(ui->loculNasteriiLineEdit->text()==globals::userCurent.loculNasterii);
    verificator|=!((ui->serieBuletinJudLineEdit->text()+" "+ui->serieBuletinCodLineEdit->text())==globals::userCurent.serieBuletin);
    return verificator;
}
bool profil::verificaIntegritate()
{
    bool verificator=true;
    verificator&=(ui->CNPLineEdit->text().length()==13);
    verificator&=(ui->serieBuletinJudLineEdit->text().length()==2);
    verificator&=(ui->serieBuletinCodLineEdit->text().length()==6);
    return verificator;
}
void profil::on_confirmaButton_clicked()
{
    if (profil::verificaSchimbari())
    {
        if (!profil::verificaIntegritate()){
            QMessageBox::critical(this,"Changements d’état d’enregistrement","les données ne sont pas valable");
            return;
        }
        QString updateProfilQuery="UPDATE `PROFIL` SET `nume`='"+
                ui->nameLineEdit->text()+"',`prenume`='"+
                ui->prenumeLineEdit->text()+"',`adresa`='"+
                ui->adresaLineEdit->text()+"',`dataNasterii`='"+
                ui->dataNasteriiEdit->date().toString("yyyy.MM.dd")+"',`loculNasterii`='"+
                ui->loculNasteriiLineEdit->text()+"',`CNP`='"+
                ui->CNPLineEdit->text()+"',`serieBuletin`='"+
                (ui->serieBuletinJudLineEdit->text()+" "+ui->serieBuletinCodLineEdit->text())+"' WHERE `id`="+
                QString::number(globals::userCurent.dbID);
        qDebug() << updateProfilQuery;
        bool executed;
        globals::cfa->query(updateProfilQuery,executed);
        if (!executed)
        {
            QMessageBox::critical(this,"Changements d’état d’enregistrement","Les changements n’ont pas été possibles en raison de problèmes de communication avec le serveur de la Banque Royale");
            qDebug() << "could not update profil " << globals::cfa->getLastError();
            return;
        }
        QMessageBox::information(this,"Changements d’état d’enregistrement","Changement réussi");
        globals::userCurent.descarcaUser();
    }
    delete this;
}

void profil::on_schimbaParolaButton_clicked()
{
    schimbareParola *schimba=new schimbareParola;
    schimba->setModal(true);
    schimba->exec();
}
