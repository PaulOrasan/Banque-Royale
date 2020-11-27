#include "headers/setarepin.h"
#include "ui_setarepin.h"
#include "headers/globals.h"
#include <QMessageBox>
setarePIN::setarePIN(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setarePIN)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->logo->setPixmap(globals::imagine->scaled(ui->logo->width(),ui->logo->height(),Qt::KeepAspectRatio));
    QRegExp regInt("[0-9]{4,4}");
    ui->oldPINLineEdit->setValidator(new QRegExpValidator(regInt,this));
    ui->newPINLineEdit->setValidator(new QRegExpValidator(regInt,this));
    ui->confirmPINLineEdit->setValidator(new QRegExpValidator(regInt,this));
}
bool setarePIN::verificareSchimbari()
{
    bool verificator=true;
    verificator&=!(ui->oldPINLineEdit->text().isEmpty() || ui->oldPINLineEdit->text().length()!=4);
    verificator&=!(ui->newPINLineEdit->text().isEmpty() ||  ui->newPINLineEdit->text().length()!=4);
    verificator&=!(ui->confirmPINLineEdit->text().isEmpty() || ui->confirmPINLineEdit->text().length()!=4);
    return verificator;
}
setarePIN::~setarePIN()
{
    delete ui;
}
void setarePIN::on_confirmButton_clicked()
{
    if (setarePIN::verificareSchimbari())
    {
        if (globals::userCurent.pin==globals::hasher.hash(ui->oldPINLineEdit->text())){
            if (ui->newPINLineEdit->text()==ui->confirmPINLineEdit->text()){
                QString updatePINQuery="UPDATE `PROFIL` SET `PIN`='"+globals::hasher.hash(ui->newPINLineEdit->text())+"' WHERE `id`="+QString::number(globals::userCurent.dbID);
                qDebug() << updatePINQuery;
                bool executed;
                globals::cfa->query(updatePINQuery,executed);
                if (!executed){
                    QMessageBox::critical(this,"Changement de statut PIN","Le code PIN ne pouvait pas être changé en raison de problèmes de communication avec le serveur de la Banque Royale");
                    qDebug() << "could not update PIN " << globals::cfa->getLastError();
                    return;
                }
                globals::userCurent.descarcaUser();
                QMessageBox::information(this,"Changement de PIN","Le code PIN a été changé avec succès");
                delete this;
            }else{
                QMessageBox::critical(this,"Changement de PIN","Confirmation de code PIN incorrect");
                return;
            }
        }else{
            QMessageBox::critical(this,"Changement de PIN","Ancien PIN incorrect");
            return;
        }
    }else{
        QMessageBox::critical(this,"Changement de PIN","Formulaire incomplet");
        return;
    }
}
