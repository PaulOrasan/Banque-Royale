#ifndef TRANZACTIE_H
#define TRANZACTIE_H

#include <QString>
#include <QDateTime>
class tranzactie
{
public:
    int id;
    QString tip;
    QDateTime dataOra;
    double valoare;
    tranzactie();
};

#endif // TRANZACTIE_H
