#include "headers/schimbareparola.h"
#include "ui_schimbareparola.h"
#include "headers/globals.h"
#include <QMessageBox>
schimbareParola::schimbareParola(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::schimbareParola)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->oldPasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->newPasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
}

schimbareParola::~schimbareParola()
{
    delete ui;
}
bool schimbareParola::verificareSchimbari()
{
    bool verificator=true;
    verificator&=!ui->oldPasswordLineEdit->text().isEmpty();
    verificator&=!ui->newPasswordLineEdit->text().isEmpty();
    verificator&=!ui->confirmPasswordLineEdit->text().isEmpty();
    return verificator;
}
void schimbareParola::on_confirmaButton_clicked()
{
    if (schimbareParola::verificareSchimbari())
    {
        QString selectPasswordQuery="SELECT `passwordHash` from `CONT` WHERE `id`="+QString::number(globals::userCurent.dbID);
        bool executed;
        globals::cfa->query(selectPasswordQuery,executed);
        if (!globals::cfa->qry->first())
        {
            qDebug() << "trouble recovering password " << globals::cfa->getLastError();
            return;
        }
        if (globals::hasher.hash(ui->oldPasswordLineEdit->text())==globals::cfa->qry->value(0).toString()){
            if (ui->newPasswordLineEdit->text()==ui->confirmPasswordLineEdit->text()){
                QString updatePasswordQuery="UPDATE `CONT` SET `passwordHash`='"+globals::hasher.hash(ui->newPasswordLineEdit->text())+"' WHERE `id`="+QString::number(globals::userCurent.dbID);
                globals::cfa->query(updatePasswordQuery,executed);
                if (!executed){
                    qDebug() << "trouble updating password " << globals::cfa->getLastError();
                    return;
                }
                QMessageBox::information(this,"Changement de mot de passe","Le mot de passe a été changé avec succès");
                delete this;
            }else{
                QMessageBox::critical(this,"Changement de mot de passe","Confirmation de mot de passe incorrect");
                return;
            }
        }else{
            QMessageBox::critical(this,"Changement de mot de passe","Ancien mot de passe incorrect");
            return;
        }
    }else{
        QMessageBox::critical(this,"Changement de mot de passe","Formulaire incomplet");
        return;
    }
}
