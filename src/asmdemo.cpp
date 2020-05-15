#include "asmdemo.h"
#include "ui_asmdemo.h"

ASMdemo::ASMdemo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ASMdemo)
{
    ui->setupUi(this);
}

ASMdemo::~ASMdemo()
{
    delete ui;
}
