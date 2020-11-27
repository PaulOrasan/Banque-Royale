#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = nullptr);
    bool verificareFormularComplet();
    bool verificareUnicitate(QString,QString);
    ~registerDialog();

private slots:
    void on_pushButton_clicked();

    void on_serieBuletinJudLineEdit_textEdited(const QString &arg1);

private:
    Ui::registerDialog *ui;
};

#endif // REGISTERDIALOG_H
