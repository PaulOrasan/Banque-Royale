#ifndef ISTORICTRANZACTII_H
#define ISTORICTRANZACTII_H

#include <QVector>
#include "tranzactie.h"
class istoricTranzactii
{
public:
    QVector<tranzactie> vecIstoric;
    void descarcaTranzactii();
    istoricTranzactii();
};

#endif // ISTORICTRANZACTII_H
