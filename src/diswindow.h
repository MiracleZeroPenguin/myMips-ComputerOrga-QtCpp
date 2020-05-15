#ifndef DISWINDOW_H
#define DISWINDOW_H

#include<QDialog>
#include<QTextDocument>
#include<QTextBlock>
#include<QString>
#include<QDebug>
#include<QFileDialog>
#include <QTextCodec>
#include<QMessageBox>
#include<QMenu>
#include<QMenuBar>
#include<QStatusBar>
namespace Ui {
class Diswindow;
}

class Diswindow : public QDialog
{
    Q_OBJECT

public:
    explicit Diswindow(QWidget *parent = nullptr);
    ~Diswindow();

private:
    Ui::Diswindow *ui;
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
};

#endif // DISWINDOW_H
