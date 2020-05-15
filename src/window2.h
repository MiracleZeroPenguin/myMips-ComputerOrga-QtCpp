#ifndef WINDOW2_H
#define WINDOW2_H

#include <QMainWindow>
#include<QTextDocument>
#include<QTextBlock>
#include<QString>
#include<QDebug>
#include<QFileDialog>
#include <QTextCodec>
#include<QMessageBox>
#include<vector>
#include<disassembler.h>
#include<copyright.h>
#include<machinedemo.h>

namespace Ui {
class Window2;
}

class Window2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window2(QWidget *parent = nullptr);
    ~Window2();

private:
    Ui::Window2 *ui;
    void createMenu();

    //for menu
public:
    QMenu* menu[10];
    QAction* act[10];
    QMenuBar* menuBar ;
    QStatusBar* status ;

public slots:
    void trigerMenu(QAction* act);

signals:
    void  sendData(QString);

private slots:
    void on_pushButton_clicked();

    void on_checkcoe_clicked(bool checked);

    void on_checkseg_clicked(bool checked);

private:
    QString GetCorrectUnicode(const QByteArray &ba);
    void fileInputtxt();        //导入txt格式coe
    void fileInputcoe();        //导入coe格式coe
    void fileSavetxt();       //导出txt格式asm
    void fileSaveasm();       //导出asm格式asm
    void clearData();           //清缓存
    bool readMachine();         //读取十六进制机器码
    bool exchange();            //转换为asm
    void outputASM();           //在文本框中输出

    QString filename;
    std::vector<QString>input;  //二进制机器码（32位）
    std::vector<QString>output; //输出
    int valid;                  //有效机器码个数
    Disassembler * mydissembler=new Disassembler;
    Copyright * mycopyright=new Copyright;
    Machinedemo * mydemo=new Machinedemo;
};

#endif // WINDOW2_H
