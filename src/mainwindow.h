#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTextDocument>
#include<QTextBlock>
#include<QString>
#include<QDebug>
#include<QFileDialog>
#include <QTextCodec>
#include<QMessageBox>
#include"assembler.h"
#include"window2.h"
#include"copyright.h"
#include"asmdemo.h"

namespace Ui {
class Mainwindow;
}

class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();
    /*struct label{
        QString name;
        int place;
    };
    std::vector<label>labellist;*/

private slots:
    void on_pushButton_clicked();

private:
    Ui::Mainwindow *ui;
    std::vector<QString>input;
    Assembler ass;
    void readASM();
    void stdASM();
    void doASM();
    void vectorclear();
    void showMachine();
    void createMenu();
    void fileInputtxt();        //导入txt格式asm
    void fileInputasm();        //导入asm格式asm
    void fileSavetxt();         //导出txt格式coe
    void fileSavecoe();         //导出coe格式coe
    QString GetCorrectUnicode(const QByteArray &ba);
    std::vector<Assembler::instruction>stdinput;
    std::vector<QString>output;
    int valid;//有效语句条数
    QString bi2hex(QString);       //2进制转16进制
    QString Hex[16] = {
        "0","1","2","3",
        "4","5","6","7",
        "8","9","A","B",
        "C","D","E","F"
    };
    QString filename;



    //for menu
public:
    QMenu* menu[10];
    QAction* act[10];
    QMenuBar* menuBar ;
    QStatusBar* status ;

public slots:
    void trigerMenu(QAction* act);

public:
    Window2 *mydis=new Window2;
    Copyright *mycopyright= new Copyright;
    ASMdemo *mydemo=new ASMdemo;

private slots:
    void receiveData(QString);

};

#endif // MAINWINDOW_H
