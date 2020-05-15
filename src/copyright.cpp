#include "copyright.h"
#include "ui_copyright.h"

Copyright::Copyright(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Copyright)
{
    ui->setupUi(this);
}

Copyright::~Copyright()
{
    delete ui;
}
