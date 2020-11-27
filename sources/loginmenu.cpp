#include "headers/loginmenu.h"
#include "ui_loginmenu.h"
#include "headers/globals.h"
#include "headers/registerdialog.h"
#include <QMessageBox>
#include "headers/menuprincipal.h"
#include "headers/despre.h"
loginMenu::loginMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::loginMenu)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    globals::cfa=new bazadate;
    if (globals::cfa->opened)
        qDebug()<<"it opens";
    else
        qDebug()<<"it doesn't open "<<globals::cfa->getLastError();
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    despre *noi=new despre;
    ui->logo->setPixmap(globals::imagine->scaled(ui->logo->width(),ui->logo->height(),Qt::KeepAspectRatio));
    noi->setModal(true);
    noi->exec();
}

loginMenu::~loginMenu()
{
    delete ui;
}

void loginMenu::on_registerPushButton_clicked()
{
    registerDialog *formular=new registerDialog;
    formular->setModal(true);
    formular->exec();
}

bool loginMenu::verificareFormularComplet()
{
    bool verificator=true;
    verificator&=!ui->emailLineEdit->text().isEmpty();
    verificator&=!ui->passwordLineEdit->text().isEmpty();
    return verificator;
}
void loginMenu::on_logInPushButton_clicked()
{
    if (loginMenu::verificareFormularComplet()) //daca formularul este completat corect
    {
        QString selectContQuery="SELECT `id`,`email`,`passwordHash` from `CONT` WHERE `email`='"+ui->emailLineEdit->text()+"'";
        qDebug() << selectContQuery;
        bool executed;
        globals::cfa->query(selectContQuery,executed); //gasesc userul cu emailul respectiv
        globals::cfa->getLastError();
        if (globals::cfa->qry->first()){
            if (globals::cfa->qry->value(2).toString()==globals::hasher.hash(ui->passwordLineEdit->text())){ //daca parola este corecta
                globals::userCurent.dbID=globals::cfa->qry->value(0).toInt();
                QString a=QString::number(globals::userCurent.dbID);
                qDebug()<<1;
                globals::userCurent.descarcaUser();
                QMessageBox::information(this,"Connexion de l’utilisateur","Enregistrement effectué avec succès");
                menuPrincipal *menu=new menuPrincipal;
                menu->setModal(true);
                menu->exec();
            }else{
                QMessageBox::critical(this,"Connexion de l’utilisateur","Ce mot de passe est incorrect");
            }
        }else if (executed){
            QMessageBox::critical(this,"Connexion de l’utilisateur","Cet utilisateur n’existe pas");
        }else{
            QMessageBox::critical(this,"Connexion au serveur","Il y avait une erreur de communication avec le serveur de la Banque Royale"+globals::cfa->getLastError());
            return;
        }
    }
}
