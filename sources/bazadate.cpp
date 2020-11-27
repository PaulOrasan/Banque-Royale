#include "headers/bazadate.h"
#include <QMessageBox>
#include <QTextStream>
bazadate::bazadate()
{
    db=QSqlDatabase::addDatabase("QODBC");
    qDebug() << QCoreApplication::applicationDirPath();
    QFile fisierLogare(QCoreApplication::applicationDirPath()+"/access.txt");
    if (!fisierLogare.open(QIODevice::ReadOnly)){
        QMessageBox::critical(0,"Eroare critica!","Nu aveti acces la baza de date! Contactati administratorul aplicatiei pentru rezolvare.");
    }
    QTextStream in(&fisierLogare);
    QString server = in.readLine();
    QString dbName = in.readLine();
    QString user = in.readLine();
    QString pass = in.readLine();

    QString dsn="Driver={MySQL ODBC 8.0 Unicode Driver};Server="+server+";Database="+dbName+";Uid="+user+";Pwd="+pass+";";
    db.setDatabaseName(dsn);
    opened=db.open();
    qry=new QSqlQuery();
}
QString bazadate::getLastError()
{
    return db.lastError().text();
}
int bazadate::getLastID()
{
    bool executed;
    bazadate::query("SELECT * FROM `CONT`",executed);
    if (executed)
    {
        int nr=0;
        while (qry->next())
            nr++;
        return nr;
    }else
    {
        return -1;
    }
}
int bazadate::getLastTranzactiiID()
{
    bool executed;
    bazadate::query("SELECT * FROM `TRANZACTII`",executed);
    if (executed)
    {
        int nr=0;
        while (qry->next())
            nr++;
        return nr;
    }else {
        return -1;
    }
}
void bazadate::query(QString queryStatement,bool& executed)
{
    if (qry->exec(queryStatement))
    {
        executed=true;
    }else
    {
        executed=false;
        qDebug() << "Error:" << qry->lastError();
    }
}
bazadate::~bazadate()
{
    db.close();
    db.removeDatabase("mysqldsn");
    qDebug() << "Am inchis conexiunea";
}
