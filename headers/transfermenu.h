#ifndef TRANSFERMENU_H
#define TRANSFERMENU_H

#include <QDialog>

namespace Ui {
class transferMenu;
}

class transferMenu : public QDialog
{
    Q_OBJECT

public:
    explicit transferMenu(QWidget *parent = nullptr);
    bool verificaFormularComplet();
    ~transferMenu();

private slots:
    void on_pushButton_clicked();

    void on_serieBuletinJudLineEdit_textEdited(const QString &arg1);

private:
    Ui::transferMenu *ui;
};

#endif // TRANSFERMENU_H
