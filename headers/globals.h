#ifndef GLOBALS_H
#define GLOBALS_H

#include "bazadate.h"
#include "user.h"
#include "hasher.h"
#include "istorictranzactii.h"
#include <QMessageBox>
#include <QPixmap>
class globals
{
public:
    static bazadate *cfa;
    static user userCurent;
    static hasher hasher;
    static istoricTranzactii istoric;
    static QPixmap *imagine;
    globals();
    static bool verificareUnicitate(QString,QString);
};

#endif // GLOBALS_H
