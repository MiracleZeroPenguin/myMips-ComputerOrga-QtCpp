#include "machinedemo.h"
#include "ui_machinedemo.h"

Machinedemo::Machinedemo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Machinedemo)
{
    ui->setupUi(this);
    ui->segcoe->hide();
}

Machinedemo::~Machinedemo()
{
    delete ui;
}

void Machinedemo::on_checkcoe_clicked(bool checked)
{
    if(checked){
        ui->checkseg->setChecked(0);
        ui->textcoe->show();
        ui->segcoe->hide();
    }
    else{
        ui->textcoe->hide();
    }
}

void Machinedemo::on_checkseg_clicked(bool checked)
{
    if(checked){
        ui->checkcoe->setChecked(0);
        ui->segcoe->show();
        ui->textcoe->hide();
    }
    else{
        ui->segcoe->hide();
    }
}
