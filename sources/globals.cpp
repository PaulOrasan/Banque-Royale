#include "headers/globals.h"

bazadate* globals::cfa;
user globals::userCurent;
hasher globals::hasher;
istoricTranzactii globals::istoric;
QPixmap* globals::imagine;
globals::globals()
{

}
bool globals::verificareUnicitate(QString email,QString CNP)
{
    QString selectQuery;
    selectQuery="SELECT * FROM `CONT` WHERE `email`='"+email+"'"; //verificare daca mai exista acest email in baza de date
    bool executed;
    globals::cfa->query(selectQuery,executed);
    if (executed)
    {
        if (globals::cfa->qry->first())
        {
            //QMessageBox::critical(this,"Inregistrare cont","Mai exista un cont cu acest email");
            return false;
        }
    }else{
        qDebug() << "could not verify email unicitate " << globals::cfa->getLastError();
        return false;
    }
    selectQuery="SELECT * FROM `PROFIL` WHERE `CNP`='"+CNP+"'"; //verificare daca mai exista acest CNP in baza de date
    globals::cfa->query(selectQuery,executed);
    if (executed)
    {
        if (globals::cfa->qry->first())
        {
            //QMessageBox::critical(this,"Inregistrare cont","Mai exista un cont cu acest CNP");
            return false;
        }
    }else{
        qDebug() << "could not verify CNP unicitate " << globals::cfa->getLastError();
        return false;
    }
    return true;
}
