#include "mainwindow.h"
#include "ui_mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
    connect(mydis,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));
    ui->machine_output->setAlternatingRowColors(true);
    ui->machine_output->setStyleSheet("alternate-background-color:#C1CBD7;background:white");
    createMenu();
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::receiveData(QString data){
    if(data=="1")
        this->show();
}

void Mainwindow::createMenu(){
    status = new QStatusBar(this);

    menu[0] = new QMenu("文件导入");
    act[0]=new QAction("*.txt",this);
    act[0]->setStatusTip("导入.txt格式的汇编语句文件");
    act[1]=new QAction("*.asm",this);
    act[1]->setStatusTip("导入.asm格式的汇编语句文件");
    menu[0]->addAction(act[0]);
    menu[0]->addAction(act[1]);

    menu[1]=new QMenu("保存机器码");
    act[2]=new QAction("另存为*.txt",this);
    act[2]->setStatusTip("导出.txt格式的机器语言文件");
    act[3]=new QAction("另存为*.coe",this);
    act[3]->setStatusTip("导出.coe格式的机器语句文件");
    menu[1]->addAction(act[2]);
    menu[1]->addAction(act[3]);

    menu[2]=new QMenu("切换模式");
    act[4]=new QAction("反汇编",this);
    act[4]->setStatusTip("现在状态：汇编模式，点击切换至反汇编模式");
    menu[2]->addAction(act[4]);

    menu[3]=new QMenu("更多信息");
    act[5]=new QAction("输入格式规定");
    act[5]->setStatusTip("输入格式/语法错误可能导致无法产生正确结果，点击查看输入格式规定");
    act[6]=new QAction("版权信息");
    act[6]->setStatusTip("原创作品，翻版必究");
    menu[3]->addAction(act[5]);
    menu[3]->addAction(act[6]);

    menuBar = new QMenuBar(this);
    menuBar->addMenu(menu[0]);
    menuBar->addMenu(menu[1]);
    menuBar->addMenu(menu[2]);
    menuBar->addMenu(menu[3]);
    menuBar->setGeometry(0,0,this->width(),30);
    connect(menuBar,SIGNAL(triggered(QAction*)),this,SLOT(trigerMenu(QAction*)));

}

void Mainwindow::trigerMenu(QAction* act)

{
    if(act->text() == "*.txt"){
        fileInputtxt();
        return;
    }
    if(act->text()=="*.asm"){
        fileInputasm();
        return;
    }
    if(act->text()=="另存为*.txt"){
        fileSavetxt();
        return;
    }
    if(act->text()=="另存为*.coe"){
        fileSavecoe();
        return;
    }
    if(act->text()=="反汇编"){
        this->close();
        mydis->show();
        return;
    }
    if(act->text()=="版权信息"){
        mycopyright->show();
        return;
    }
    if(act->text()=="输入格式规定"){
        mydemo->show();
        return;
    }
}



void Mainwindow::fileSavecoe(){
    QString str="memory_initialization_radix=16;\nmemory_initialization_vector=\n";
    for(int i=0;i<valid-1;i++){
        str=str+output[i]+",";
        if(i%8==7)str=str+"\n";
    }
    str=str+output[valid-1]+";";

    QFileDialog fileDialog;
    QString fileName=fileDialog.getSaveFileName(this,tr("open File"),"D:\\",tr("COE File(*.coe)"));
    if(fileName == "")
        return;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
        return;
    }
    else
       {
           QTextStream textStream(&file);
           textStream<<str;
           QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
           file.close();
       }
}

void Mainwindow::fileSavetxt(){
    QString str="";
    for(int i=0;i<valid;i++){
        str=str+output[i]+"\n";
    }

    QFileDialog fileDialog;
    QString fileName=fileDialog.getSaveFileName(this,tr("open File"),"D:\\",tr("Text File(*.txt)"));
    if(fileName == "")
        return;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
        return;
    }
    else
       {
           QTextStream textStream(&file);
           textStream<<str;
           QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
           file.close();
       }
}

void Mainwindow::fileInputasm(){
    ui->asm_input->clear();
    filename=QFileDialog::getOpenFileName(this,tr("选择文件"),"D:\\",tr("*.asm"));
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    QString str=GetCorrectUnicode(t);
    ui->asm_input->setPlainText(str);
    file.close();
}

QString Mainwindow::GetCorrectUnicode(const QByteArray &ba){
    QTextCodec::ConverterState state;
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QString text = codec->toUnicode(ba.constData(), ba.size(), &state);
        if (state.invalidChars > 0)
            text = QTextCodec::codecForName("GBK")->toUnicode(ba);
        else
            text = ba;
        return text;
}

void Mainwindow::fileInputtxt(){
    ui->asm_input->clear();
    filename=QFileDialog::getOpenFileName(this,tr("选择文件"),"D:\\",tr("*.txt"));
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    QString str=GetCorrectUnicode(t);
    ui->asm_input->setPlainText(str);
    file.close();
}

void Mainwindow::on_pushButton_clicked()
{
    vectorclear();  //堆栈清空
    readASM();      //读取
    stdASM();       //标准化
    doASM();        //进行机器码的转换
    showMachine();  //显示在表格中

}
void Mainwindow::vectorclear(){
    input.clear();
    stdinput.clear();
    ass.labellist.clear();
    ass.valid=0;
    output.clear();

}

void Mainwindow::showMachine(){

    ui->machine_output->setRowCount(valid);
    for(int i=0;i<valid;i++){
        int addr=i*4;
        QString address=ass.int2Binary(addr,16);
        address=bi2hex(address);
        ui->machine_output->setItem(i,0,new QTableWidgetItem(address.mid(0,4)));
        for(int j=0;j<8;j++){
            ui->machine_output->setItem(i,j+1,new QTableWidgetItem(output[i].mid(j,1)));
        }
    }

    ui->machine_output->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Mainwindow::doASM(){
    for(int i=0;i<valid;i++){
        //qDebug()<<stdinput[i].type<<stdinput[i].func<<stdinput[i].valueline;
        //qDebug()<<ass.asm2machine(stdinput[i]);
        output.push_back(ass.asm2machine(stdinput[i]));
        output[i]=bi2hex(output[i]);
        qDebug()<<output[i];
    }
}

QString Mainwindow::bi2hex(QString in){
    QString out="";
    for(int i=0;i<8;i++){
        int b3,b2,b1,b0;
        b3=in.mid(4*i,1).toInt();
        b2=in.mid(4*i+1,1).toInt();
        b1=in.mid(4*i+2,1).toInt();
        b0=in.mid(4*i+3,1).toInt();
        int tmp=b3*8+b2*4+b1*2+b0;
        out=out+Hex[tmp];
    }
    return out;
}

void Mainwindow::stdASM(){
    valid=0;
    for(int i=0;i<input.size();i++){
        QList<QString>lst;
        lst=input[i].split(" ");
        if(input[i].isEmpty()||input[i].mid(0,2)=="//"){
            //注释行或空行
        }
        else if(lst[0].mid(lst[0].length()-1,1)==":"){
            //label行
            //struct label newLabel;
            struct Assembler::label newLabel;
            newLabel.name=lst[0].mid(0,lst[0].length()-1);
            newLabel.place=valid;
            qDebug()<<newLabel.name<<newLabel.place;
            ass.labellist.push_back(newLabel);
        }
        else{
            char type=ass.getType(lst[0]);
            if(type!='x'){
                //struct instruction ins;
                struct Assembler::instruction ins;
                ins.type=type;
                ins.func=lst[0];
                QString vline;
                for(int j=1;j<lst.size();j++){
                    if(lst[j].mid(0,2)!="//")
                        vline=vline+lst[j];
                    else
                        break;//开始注释
                }
                ins.valueline=vline;
                stdinput.push_back(ins);
                //qDebug()<<stdinput[valid].type<<stdinput[valid].func<<stdinput[valid].valueline;
                valid++;
            }
        }
    }
}

void Mainwindow::readASM(){
    QTextDocument* doc=ui->asm_input->document();
    int n=doc->lineCount();
    for(int x=0;x<n;x++){
        QTextBlock textLine=doc->findBlockByNumber (x) ;
        QString text=textLine.text();
        input.push_back(textLine.text());
        //qDebug()<<input[x];
    }
    //qDebug()<<input.size();
}
