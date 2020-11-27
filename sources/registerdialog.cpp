#include "headers/registerdialog.h"
#include "ui_registerdialog.h"
#include "headers/globals.h"
#include <QMessageBox>
registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    //setare politica de acceptare a caracterelor
    ui->genComboBox->insertItem(1,"Feminim");
    ui->genComboBox->insertItem(2,"Masculin");
    ui->genComboBox->setCurrentIndex(-1);
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
    QRegExp regPIN("[0-9]{4,4}");
    ui->PINLineEdit->setValidator(new QRegExpValidator(regPIN,this));
}

registerDialog::~registerDialog()
{
    delete ui;
}
bool registerDialog::verificareFormularComplet()
{
    //fiecare casuta trebuie completata
    bool verificator=true;
    verificator&=!ui->nameLineEdit->text().isEmpty();
    verificator&=!ui->prenumeLineEdit->text().isEmpty();
    verificator&=!ui->CNPLabel->text().isEmpty();
    verificator&=!ui->serieBuletinCodLineEdit->text().isEmpty();
    verificator&=!ui->serieBuletinJudLineEdit->text().isEmpty();
    verificator&=!ui->adresaLineEdit->text().isEmpty();
    verificator&=!ui->loculNasteriiLineEdit->text().isEmpty();
    verificator&=!ui->emailLineEdit->text().isEmpty();
    verificator&=!ui->passwordLineEdit->text().isEmpty();
    verificator&=!ui->genComboBox->currentText().isEmpty();
    verificator&=!ui->PINLineEdit->text().isEmpty();
    return verificator;
}
void registerDialog::on_pushButton_clicked()
{
    if (registerDialog::verificareFormularComplet())
    {
        if (ui->CNPLineEdit->text().length()!=13)
        {
            QMessageBox::critical(this,"CNP","S'il vous plaît introduisez un CNP valable");
            return;
        }
        if (ui->serieBuletinJudLineEdit->text().length()!=2)
        {
            QMessageBox::critical(this,"Numéro de la carte d’identité du destinataire ","S'il vous plaît introduisez un code de département valable");
            return;
        }
        if (ui->serieBuletinCodLineEdit->text().length()!=6)
        {
            QMessageBox::critical(this,"Numéro de la carte d’identité du destinataire ","S'il vous plaît introduisez un numéro de carte d'identité valable");
            return;
        }
        if (!globals::verificareUnicitate(ui->emailLineEdit->text(),ui->CNPLineEdit->text()))
        {
            QMessageBox::critical(this,"Registre d’état","Il y a un compte avec cet mail ou avec cet CNP");
            return;
        }
        globals::cfa->lastID=globals::cfa->getLastID()+1;
        QString insertNewContQuery="INSERT INTO `CONT`(`id`,`email`,`passwordHash`) VALUES ("+ //inserare cont nou
                QString::number(globals::cfa->lastID)+",'"+
                ui->emailLineEdit->text()+"','"+
                globals::hasher.hash(ui->passwordLineEdit->text())+"')";
        bool executed;
        globals::cfa->query(insertNewContQuery,executed);
        if (!executed)
        {
            QMessageBox::critical(this,"Registre d’état","L’enregistrement  n’a pas pu être effectué en raison des problèmes de communication avec le serveur de la Banque Royale");
            qDebug() << globals::cfa->getLastError();
            return;
        }
        QString insertNewProfilQuery="INSERT INTO `PROFIL`(`id`,`nume`,`prenume`,`adresa`,`dataNasterii`,`loculNasterii`,`CNP`,`serieBuletin`,`codBancar`,`PIN`) VALUES ("+
                QString::number(globals::cfa->lastID)+",'"+
                ui->nameLineEdit->text()+"','"+
                ui->prenumeLineEdit->text()+"','"+
                ui->adresaLineEdit->text()+"','"+
                ui->dataNasteriiEdit->date().toString("yyyy.MM.dd")+"','"+
                ui->loculNasteriiLineEdit->text()+"','"+
                ui->CNPLineEdit->text()+"','"+
                (ui->serieBuletinJudLineEdit->text()+" "+ui->serieBuletinCodLineEdit->text())+"','"+
                globals::userCurent.generareCodBancar()+"','"+
                globals::hasher.hash(ui->PINLineEdit->text())+"')";
        qDebug() << insertNewProfilQuery;
        globals::cfa->query(insertNewProfilQuery,executed); //inserare profil nou
        if (!executed)
        {
            qDebug() << "Could not insert new user into PROFIL " <<globals::cfa->getLastError();
            QString deleteNewContQuery="DELETE FROM `CONT` WHERE `id`="+QString::number(globals::cfa->lastID);
            globals::cfa->query(deleteNewContQuery,executed);
            return;
        }
        QString insertNewBalantaQuery="INSERT INTO `BALANTA`(`id`,`valoare`,`datorie`) VALUES ("+
                QString::number(globals::cfa->lastID)+","+
                QString::number(0)+","+
                QString::number(0)+")";
        qDebug() << insertNewBalantaQuery;
        globals::cfa->query(insertNewBalantaQuery,executed); //inserare balanta noua
        if (!executed)
        {
            qDebug() << "Could not insert new user into BALANTA " <<globals::cfa->getLastError();
            QString deleteNewContQuery="DELETE FROM `CONT` WHERE `id`="+QString::number(globals::cfa->lastID);
            globals::cfa->query(deleteNewContQuery,executed);
            deleteNewContQuery="DELETE FROM `PROFIL` WHERE `id`="+QString::number(globals::cfa->lastID);
            globals::cfa->query(deleteNewContQuery,executed);
            return;
        }
        QMessageBox::information(this,"Registre d’état","Enregistrement nouvel utilisateur avec succès");
        delete this;
    }else{
        QMessageBox::critical(this,"Registre d’état","Formulaire incomplet");
        return;
    }
}

void registerDialog::on_serieBuletinJudLineEdit_textEdited(const QString &arg1)
{
    ui->serieBuletinJudLineEdit->setText(arg1.toUpper()); //caracterele mereu litere mari
}
