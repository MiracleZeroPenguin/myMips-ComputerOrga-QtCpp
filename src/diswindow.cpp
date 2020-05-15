#include "diswindow.h"
#include "ui_diswindow.h"

Diswindow::Diswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Diswindow)
{
    ui->setupUi(this);
    createMenu();
}

Diswindow::~Diswindow()
{
    delete ui;
}

void Diswindow::createMenu(){
    status = new QStatusBar(this);

    menu[0] = new QMenu("文件导入");
    act[0]=new QAction("*.txt",this);
    act[0]->setStatusTip("导入.txt格式的机器语句文件");
    act[1]=new QAction("*.coe",this);
    act[1]->setStatusTip("导入.coe格式的机器语句文件");
    menu[0]->addAction(act[0]);
    menu[0]->addAction(act[1]);

    menu[1]=new QMenu("保存汇编码");
    act[2]=new QAction("另存为*.txt",this);
    act[2]->setStatusTip("导出.txt格式的汇编语言文件");
    act[3]=new QAction("另存为*.asm",this);
    act[3]->setStatusTip("导出.asm格式的汇编语句文件");
    menu[1]->addAction(act[2]);
    menu[1]->addAction(act[3]);

    menu[2]=new QMenu("切换");
    act[4]=new QAction("汇编",this);
    act[4]->setStatusTip("现在状态：反汇编模式，点击切换至汇编模式");
    menu[2]->addAction(act[4]);

    menuBar = new QMenuBar(this);
    menuBar->addMenu(menu[0]);
    menuBar->addMenu(menu[1]);
    menuBar->addMenu(menu[2]);
    menuBar->setGeometry(0,0,this->width(),30);
    connect(menuBar,SIGNAL(triggered(QAction*)),this,SLOT(trigerMenu(QAction*)));
}

void Diswindow::trigerMenu(QAction* act)
{
    if(act->text()=="汇编"){
        emit sendData("1");
        this->close();
    }
}
