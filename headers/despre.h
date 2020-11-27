#ifndef DESPRE_H
#define DESPRE_H

#include <QDialog>

namespace Ui {
class despre;
}

class despre : public QDialog
{
    Q_OBJECT

public:
    explicit despre(QWidget *parent = nullptr);
    ~despre();

private:
    Ui::despre *ui;
};

#endif // DESPRE_H
