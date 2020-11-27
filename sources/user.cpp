#include "headers/user.h"
#include "headers/globals.h"
user::user()
{

}
void user::descarcaUser()
{
    QString selectProfilQuery="SELECT `id`, `nume`, `prenume`, `adresa`, `dataNasterii`, `loculNasterii`, `CNP`, `serieBuletin`,`codBancar`,`PIN` FROM `PROFIL` WHERE `id`="+
            QString::number(globals::userCurent.dbID);
    qDebug() << selectProfilQuery;
    bool executed;
    globals::cfa->query(selectProfilQuery,executed);
    if (!globals::cfa->qry->first()){
        qDebug() << "trouble recovering user info" << globals::cfa->getLastError();
        return;
    }
    globals::userCurent.nume=globals::cfa->qry->value(1).toString();
    globals::userCurent.prenume=globals::cfa->qry->value(2).toString();
    globals::userCurent.adresa=globals::cfa->qry->value(3).toString();
    globals::userCurent.dataNasterii=globals::cfa->qry->value(4).toDate();
    globals::userCurent.loculNasterii=globals::cfa->qry->value(5).toString();
    globals::userCurent.CNP=globals::cfa->qry->value(6).toString();
    globals::userCurent.serieBuletin=globals::cfa->qry->value(7).toString();
    globals::userCurent.codBancar=globals::cfa->qry->value(8).toString();
    globals::userCurent.pin=globals::cfa->qry->value(9).toString();
    globals::userCurent.userOnline=true;
    QString selectBalantaQuery="SELECT `id`,`valoare`,`datorie` FROM `BALANTA` WHERE `id`=" + QString::number(globals::userCurent.dbID);
    globals::cfa->query(selectBalantaQuery,executed);
    if (!globals::cfa->qry->first()){
        qDebug() << "trouble recovering cash info" << globals::cfa->getLastError();
        return;
    }
    globals::userCurent.valoare=globals::cfa->qry->value(1).toDouble();
    globals::userCurent.datorie=globals::cfa->qry->value(2).toDouble();
    qDebug() << "downloaded user";
}
QString user::generareCodBancar()
{
    QRandomGenerator generator;
    generator.seed(time(NULL));
    QString cod;
    int low=1000,high=9999;
    cod+=(QString::number(generator.bounded(low,high)));
    cod+=(QString::number(generator.bounded(low,high)));
    cod+=(QString::number(generator.bounded(low,high)));
    cod+=(QString::number(generator.bounded(low,high)));
    return cod;
}
QString user::generarePin()
{
    QRandomGenerator generator;
    generator.seed(time(NULL)+1);
    int low=1000,high=9999;
    return QString::number(generator.bounded(low,high));

}
