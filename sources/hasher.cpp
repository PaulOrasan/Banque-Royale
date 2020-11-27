#include "headers/hasher.h"

hasher::hasher()
{

}
QString hasher::hash(QString input)
{
    QByteArray result=QCryptographicHash::hash(input.toUtf8(),QCryptographicHash::Md5);
    return QLatin1String(result.toHex());
}
