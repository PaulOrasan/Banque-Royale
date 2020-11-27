#include "headers/istorictranzactii.h"
#include "headers/globals.h"
istoricTranzactii::istoricTranzactii()
{

}
void istoricTranzactii::descarcaTranzactii()
{
    this->vecIstoric.clear();
    qDebug() << globals::userCurent.dbID;
    qDebug() << "descarc tranzactii";
    QString selectTranzactiiQuery="SELECT `data/ora`,`tip`,`valoare` FROM `TRANZACTII` WHERE `contFK`="+QString::number(globals::userCurent.dbID);
    bool executed;
    qDebug() << selectTranzactiiQuery;
    globals::cfa->query(selectTranzactiiQuery,executed);
    if (!globals::cfa->qry->first()){
        qDebug() << selectTranzactiiQuery << "trouble recovering tranzactii " << globals::cfa->getLastError();
        return;
    }
    qDebug() << "am ajuns aici";
    tranzactie container;
    int nr=1;
    container.id=nr;
    container.dataOra=globals::cfa->qry->value(0).toDateTime();
    container.tip=globals::cfa->qry->value(1).toString();
    container.valoare=globals::cfa->qry->value(2).toDouble();
    this->vecIstoric.push_back(container);
    while (globals::cfa->qry->next()){
        nr++;
        container.id=nr;
        container.dataOra=globals::cfa->qry->value(0).toDateTime();
        container.tip=globals::cfa->qry->value(1).toString();
        container.valoare=globals::cfa->qry->value(2).toDouble();
        this->vecIstoric.push_back(container);
    }
    qDebug() << "am descarcat tranzactii";
}
