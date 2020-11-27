#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>
class user
{
public:
    QString nume;
    QString prenume;
    QString CNP;
    QString serieBuletin;
    QDate dataNasterii;
    QString loculNasterii;
    QString adresa;
    QString codBancar;
    QString pin;
    bool userOnline=false;
    double valoare;
    double datorie;
    int dbID;
    void descarcaUser();
    QString generareCodBancar();
    QString generarePin();
    user();
};
#endif // USER_H
