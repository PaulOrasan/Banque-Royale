#include "headers/despre.h"
#include "ui_despre.h"
#include "headers/globals.h"
despre::despre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::despre)
{
    ui->setupUi(this);
    globals::imagine=new QPixmap(":/imagini/Logo.png");
    ui->logo->setPixmap(globals::imagine->scaled(ui->logo->width(),ui->logo->height(),Qt::KeepAspectRatio));
    this->setFixedSize(this->width(),this->height());
}

despre::~despre()
{
    delete ui;
}
