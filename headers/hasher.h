#ifndef HASHER_H
#define HASHER_H

#include <QString>
#include <QCryptographicHash>
class hasher
{
public:
    hasher();
    QString hash(QString input);
};

#endif // HASHER_H
