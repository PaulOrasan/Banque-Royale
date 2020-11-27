#ifndef SETAREPIN_H
#define SETAREPIN_H

#include <QDialog>

namespace Ui {
class setarePIN;
}

class setarePIN : public QDialog
{
    Q_OBJECT

public:
    explicit setarePIN(QWidget *parent = nullptr);
    bool verificareSchimbari();
    ~setarePIN();

private slots:

    void on_confirmButton_clicked();

private:
    Ui::setarePIN *ui;
};

#endif // SETAREPIN_H
