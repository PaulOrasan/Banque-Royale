#include "headers/vizualizareistoric.h"
#include "ui_vizualizareistoric.h"
#include "headers/globals.h"
vizualizareIstoric::vizualizareIstoric(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vizualizareIstoric)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());
    ui->istoricTable->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->istoricTable->setRowCount(globals::cfa->lastTranzactiiID);
    ui->istoricTable->setColumnWidth(3,ui->istoricTable->columnWidth(3)*(double)1.2);
    globals::istoric.descarcaTranzactii();
    int size=globals::istoric.vecIstoric.size();
    for (int i=0; i<size; i++)
        vizualizareIstoric::displayTranzactie(globals::istoric.vecIstoric.at(i),i);
    ui->logo->setPixmap(globals::imagine->scaled(ui->logo->width(),ui->logo->height(),Qt::KeepAspectRatio));
}

vizualizareIstoric::~vizualizareIstoric()
{
    delete ui;
}
void vizualizareIstoric::displayTranzactie(tranzactie container,int row)
{
    ui->istoricTable->insertRow(row);
    QTableWidgetItem *id=new QTableWidgetItem;
    id->setText(QString::number(container.id));
    ui->istoricTable->setItem(row,0,id);
    QTableWidgetItem *tip=new QTableWidgetItem;
    tip->setText(container.tip);
    ui->istoricTable->setItem(row,1,tip);
    QTableWidgetItem *valoare=new QTableWidgetItem;
    valoare->setText(QString::number(container.valoare));
    ui->istoricTable->setItem(row,2,valoare);
    QTableWidgetItem *dataOra=new QTableWidgetItem;
    dataOra->setText(container.dataOra.toString("yyyy.MM.dd.hh.mm.ss"));
    ui->istoricTable->setItem(row,3,dataOra);
}

void vizualizareIstoric::on_confirmButton_clicked()
{
    delete this;
}
