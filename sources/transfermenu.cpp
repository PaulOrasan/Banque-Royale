#include "headers/transfermenu.h"
#include "ui_transfermenu.h"
#include <QMessageBox>
#include "headers/globals.h"
transferMenu::transferMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::transferMenu)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    QRegExp regInt("[0-9]{13,13}");
    ui->CNPLineEdit->setValidator(new QRegExpValidator(regInt,this));
    ui->serieBuletinCodLineEdit->setValidator(new QIntValidator);
    ui->serieBuletinCodLineEdit->setMaxLength(6);
    QRegExp regChar("[A-Za-z]{1,2}");
    ui->serieBuletinJudLineEdit->setValidator(new QRegExpValidator(regChar,this));
    QRegExp regNume("[A-Za-z -]{30,30}");
    ui->numeLineEdit->setValidator(new QRegExpValidator(regNume,this));
    ui->prenumeLineEdit->setValidator(new QRegExpValidator(regNume,this));
    ui->valoareSpinBox->setRange(0,globals::userCurent.valoare);
    QRegExp regPIN("[0-9]{4,4}");
    ui->PINLineEdit->setValidator(new QRegExpValidator(regPIN,this));
    ui->codPrimaLineEdit->setValidator(new QRegExpValidator(regPIN,this));
    ui->codaDouaLineEdit->setValidator(new QRegExpValidator(regPIN,this));
    ui->codaTreiaLineEdit->setValidator(new QRegExpValidator(regPIN,this));
    ui->codaPatraLineEdit->setValidator(new QRegExpValidator(regPIN,this));
}

transferMenu::~transferMenu()
{
    delete ui;
}
bool transferMenu::verificaFormularComplet()
{
    bool verificator=true;
    verificator&=!ui->numeLineEdit->text().isEmpty();
    verificator&=!ui->prenumeLineEdit->text().isEmpty();
    verificator&=!ui->CNPLineEdit->text().isEmpty();
    verificator&=!ui->serieBuletinJudLineEdit->text().isEmpty();
    verificator&=!ui->serieBuletinCodLineEdit->text().isEmpty();
    verificator&=!ui->codPrimaLineEdit->text().isEmpty();
    verificator&=!ui->codaDouaLineEdit->text().isEmpty();
    verificator&=!ui->codaTreiaLineEdit->text().isEmpty();
    verificator&=!ui->codaPatraLineEdit->text().isEmpty();
    verificator&=!ui->PINLineEdit->text().isEmpty();
  /*  if (verificator){
        if (ui->CNPLineEdit->text().length()!=13){
            QMessageBox::critical(this,"Statut de transfert","Va rog completati CNP-ul complet");
            return false;
        }
        if (ui->serieBuletinJudLineEdit->text().length()!=2 || ui->serieBuletinCodLineEdit->text().length()!=6){
            QMessageBox::critical(this,"Statut de transfert","Va rog completati seria buletinului completa");
            return false;
        }
        int prima=ui->codPrimaLineEdit->text().length(),adoua=ui->codaDouaLineEdit->text().length();
        int atreia=ui->codaTreiaLineEdit->text().length(),apatra=ui->codaPatraLineEdit->text().length();
        if (prima!=4 || adoua!=4 || atreia!=4 || apatra!=4){
            QMessageBox::critical(this,"Statut de transfert","Va rog completati codul bancar complet");
            return false;
        }
    }*/
    return verificator;
}

void transferMenu::on_pushButton_clicked()
{
    if (transferMenu::verificaFormularComplet()){
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
        if (globals::hasher.hash(ui->PINLineEdit->text())!=globals::userCurent.pin){
            QMessageBox::critical(this,"Statut de transfert","Le PIN introduit est incorrect");
            return;
        }
        if (!(ui->valoareSpinBox->value()>0)){
            QMessageBox::critical(this,"Statut de transfert","Choisissez une valeur");
            return;
        }
        QString selectReceiverQuery="SELECT `id` FROM `PROFIL` WHERE `nume`='"+
                ui->numeLineEdit->text()+"' AND `prenume`='"+
                ui->prenumeLineEdit->text()+"' AND `CNP`='"+
                ui->CNPLineEdit->text()+"' AND `serieBuletin`='"+
                (ui->serieBuletinJudLineEdit->text()+" "+ui->serieBuletinCodLineEdit->text())+"' AND `codBancar`='"+
                (ui->codPrimaLineEdit->text()+ui->codaDouaLineEdit->text()+ui->codaTreiaLineEdit->text()+ui->codaPatraLineEdit->text())+"'";
        qDebug() << selectReceiverQuery;
        bool executed;
        globals::cfa->query(selectReceiverQuery,executed);
        if (!globals::cfa->qry->first()){
            QMessageBox::critical(this,"Statut de transfert","On n’a trouvé aucun utilisateur avec ces données.  Vérifiez et assurez-vous que les données soient correctes.");
            return;
        }
        int receiverID=globals::cfa->qry->value(0).toInt();
        QString updateBalantaQuery="UPDATE `BALANTA` SET `valoare`=`valoare`-"+QString::number(ui->valoareSpinBox->value())+
                " WHERE `id`="+QString::number(globals::userCurent.dbID);
        qDebug() << updateBalantaQuery;
        globals::cfa->query(updateBalantaQuery,executed);
        if (!executed){
            QMessageBox::critical(this,"Statut de transfert","Le transfert ne peut être réalisé en raison de problèmes de communication avec le serveur de la Banque Royale");
            qDebug() << "trouble updating balanta for sender " << globals::cfa->getLastError();
            return;
        }
        globals::cfa->lastTranzactiiID=globals::cfa->getLastTranzactiiID()+1;
        QString insertTranzactieQuery="INSERT INTO `TRANZACTII`(`id`,`data/ora`, `tip`, `valoare`, `contFK`) VALUES ("+
                QString::number(globals::cfa->lastTranzactiiID)+",'"+
                QDateTime::currentDateTime().toString("yyyy.MM.dd.hh.mm.ss")+"','ENVOYER',"+
                QString::number(ui->valoareSpinBox->value())+","+QString::number(globals::userCurent.dbID)+")";
        qDebug() << insertTranzactieQuery;
        globals::cfa->query(insertTranzactieQuery,executed);
        if (!executed){
            qDebug() << "could not insert trimitere tranzactie " << globals::cfa->getLastError();
            return;
        }
        updateBalantaQuery="UPDATE `BALANTA` SET `valoare`=`valoare`+"+QString::number(ui->valoareSpinBox->value())+
                " WHERE `id`="+QString::number(receiverID);
        qDebug() << updateBalantaQuery;
        globals::cfa->query(updateBalantaQuery,executed);
        if (!executed){
            qDebug() << "trouble updating value for receiver " << globals::cfa->getLastError();
            return;
        }
        insertTranzactieQuery="INSERT INTO `TRANZACTII`(`id`,`data/ora`, `tip`, `valoare`, `contFK`) VALUES ("+
                QString::number(globals::cfa->lastTranzactiiID+1)+",'"+
                QDateTime::currentDateTime().toString("yyyy.MM.dd.hh.mm.ss")+"','REÇEVOIR',"+
                QString::number(ui->valoareSpinBox->value())+","+QString::number(receiverID)+")";
        qDebug() << insertTranzactieQuery;
        globals::cfa->query(insertTranzactieQuery,executed);
        if (!executed){
            qDebug() << "could not insert primire tranzactie" << globals::cfa->getLastError();
            return;
        }
        QMessageBox::information(this,"Statut de transfert","Vous avez réussi le transfert "+QString::number(ui->valoareSpinBox->value())+" euro lui "+
                                 ui->numeLineEdit->text()+" "+ui->prenumeLineEdit->text());
        delete this;
    }else{
        QMessageBox::critical(this,"Statut de transfert","Formulaire incomplet, veuillez remplir le formulaire correctement");
        return;
    }
}

void transferMenu::on_serieBuletinJudLineEdit_textEdited(const QString &arg1)
{
    ui->serieBuletinJudLineEdit->setText(arg1.toUpper());
}
