#ifndef BAZADATE_H
#define BAZADATE_H
#include <QDebug>
#include <QtSql>
#include <QString>
class bazadate
{
    public:
        QSqlDatabase db;
        QSqlQuery *qry;
        bool opened;
        int lastID=0;
        int lastTranzactiiID=0;
        bazadate();
        void query(QString queryStatement,bool& executed);
        QString getLastError();
        int getLastID();
        int getLastTranzactiiID();
        ~bazadate();
};

#endif // BAZADATE_H
