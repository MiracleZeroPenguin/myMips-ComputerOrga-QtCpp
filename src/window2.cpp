#include "window2.h"
#include "ui_window2.h"

Window2::Window2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window2)
{
    ui->setupUi(this);
    createMenu();
}

Window2::~Window2()
{
    delete ui;
}

void Window2::createMenu(){
    status = new QStatusBar(this);

    menu[0] = new QMenu("文件导入");
    act[0]=new QAction("*.txt",this);
    act[0]->setStatusTip("导入.txt格式的机器语句文件，格式为0000: 08000008");
    act[1]=new QAction("*.coe",this);
    act[1]->setStatusTip("导入.coe格式的机器语句文件，格式为标准coe");
    menu[0]->addAction(act[0]);
    menu[0]->addAction(act[1]);

    menu[1]=new QMenu("保存汇编码");
    act[2]=new QAction("另存为*.txt",this);
    act[2]->setStatusTip("导出.txt格式的汇编语言文件");
    act[3]=new QAction("另存为*.asm",this);
    act[3]->setStatusTip("导出.asm格式的汇编语句文件");
    menu[1]->addAction(act[2]);
    menu[1]->addAction(act[3]);

    menu[2]=new QMenu("切换模式");
    act[4]=new QAction("汇编",this);
    act[4]->setStatusTip("现在状态：反汇编模式，点击切换至汇编模式");
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

void Window2::trigerMenu(QAction* act)
{
    if(act->text()=="汇编"){
        emit sendData("1");
        this->close();
        return;
    }
    if(act->text()=="*.txt"){
        fileInputtxt();
        return;
    }
    if(act->text()=="*.coe"){
        fileInputcoe();
        return;
    }
    if(act->text()=="另存为*.txt"){
        fileSavetxt();
        return;
    }
    if(act->text()=="另存为*.asm"){
        fileSaveasm();
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

void Window2::fileSaveasm(){
    QString str="";
    str=ui->asm_output->toPlainText();

    QFileDialog fileDialog;
    QString fileName=fileDialog.getSaveFileName(this,tr("open File"),"D:\\",tr("Text File(*.asm)"));
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

void Window2::fileSavetxt(){
    QString str="";
    str=ui->asm_output->toPlainText();

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

void Window2::fileInputcoe(){
    ui->coe_input->clear();
    filename=QFileDialog::getOpenFileName(this,tr("选择文件"),"D:\\",tr("*.coe"));
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    QString str=GetCorrectUnicode(t);
    ui->coe_input->setPlainText(str);
    file.close();
    ui->checkcoe->setChecked(1);
    ui->checkseg->setChecked(0);
}

void Window2::fileInputtxt(){
    ui->coe_input->clear();
    filename=QFileDialog::getOpenFileName(this,tr("选择文件"),"D:\\",tr("*.txt"));
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    QString str=GetCorrectUnicode(t);
    ui->coe_input->setPlainText(str);
    file.close();
    ui->checkcoe->setChecked(0);
    ui->checkseg->setChecked(1);
}

QString Window2::GetCorrectUnicode(const QByteArray &ba){
    QTextCodec::ConverterState state;
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QString text = codec->toUnicode(ba.constData(), ba.size(), &state);
        if (state.invalidChars > 0)
            text = QTextCodec::codecForName("GBK")->toUnicode(ba);
        else
            text = ba;
        return text;
}

void Window2::on_pushButton_clicked()
{
    clearData();
    if(!readMachine())return;
    if(!exchange())return;
    outputASM();
}

void Window2::outputASM(){
    QString str="";
    for(int i=0;i<output.size();i++){
        for(int j=0;j<mydissembler->labellist.size();j++){
            if(mydissembler->labellist[j].place==i){
                str=str+"\n"+mydissembler->labellist[j].name+":\n";
                break;
            }
        }
        str=str+output[i]+"\n";
    }
    for(int j=0;j<mydissembler->labellist.size();j++){
        if(mydissembler->labellist[j].place==output.size()){
            str=str+"\n"+mydissembler->labellist[j].name+":\n";
            break;
        }
    }
    ui->asm_output->setPlainText(str);
}

void Window2::clearData(){
    valid=0;
    input.clear();
    output.clear();
    mydissembler->labellist.clear();
    mydissembler->valid=0;
}

bool Window2::exchange(){
    QString type;
    QString instruction;
    for(int i=0;i<input.size();i++){
        type=mydissembler->getType(input[i].mid(0,6));
        qDebug()<<type<<input[i].mid(0,6);
        if(type=="error")return false;
        else if (type=="i") {
            instruction=mydissembler->trans_itype(input[i]);
            output.push_back(instruction);
        }
        else if (type=="j") {
            instruction=mydissembler->trans_jtype(input[i]);
            output.push_back(instruction);
        }
        else{
            //r
            instruction=mydissembler->trans_rtype(input[i]);
            output.push_back(instruction);
        }
    }
    return true;
}

bool Window2::readMachine(){
    QTextDocument* doc=ui->coe_input->document();
    int n=doc->lineCount();
    if(ui->checkcoe->isChecked()){
        int k=0;
        QTextBlock textLine;
        QString text;
        for(int x=0;x<n;x++){
            textLine=doc->findBlockByNumber (x) ;
            text=textLine.text();
            if(text.isEmpty()){
                continue;
            }
            if(k==0){
                if(text!="memory_initialization_radix=16;"){
                    QMessageBox::warning(this,tr("错误"),tr("请选择输入正确.coe格式"));
                    return false;
                }
            }
            else if(k==1){
                if(text!="memory_initialization_vector="){
                    QMessageBox::warning(this,tr("错误"),tr("请选择输入正确.coe格式"));
                    return false;
                }
            }
            else{
                QList<QString>lst;
                text=text.simplified();
                lst=text.split(",");
                if(x==n-1){
                    lst[lst.size()-1]=lst[lst.size()-1].mid(0,lst[lst.size()-1].length()-1);
                }
                for(int j=0;j<lst.size();j++){
                    lst[j]=lst[j].simplified();
                    if(lst[j].isEmpty())continue;
                    if(mydissembler->hex2bi(lst[j])=="error"){
                        QMessageBox::warning(this,tr("错误"),tr("请选择输入正确的十六进制机器码"));
                        return false;
                    }
                    else{
                        input.push_back(mydissembler->hex2bi(lst[j]));
                        //qDebug()<<input[valid];
                        valid++;
                    }
                }
            }
            k++;
        }
        return true;
    }
    else if(ui->checkseg->isChecked()){
        QTextBlock textLine;
        QString text;
        for(int x=0;x<n;x++){
            textLine=doc->findBlockByNumber (x) ;
            text=textLine.text().simplified();
            if(text.isEmpty()){
                continue;
            }
            QList<QString>lst;
            lst=text.split(",");
            for(int j=0;j<lst.size();j++){
                lst[j]=lst[j].simplified();
                if(lst[j].isEmpty())continue;
                if(mydissembler->hex2bi(lst[j])=="error"){
                    QMessageBox::warning(this,tr("错误"),tr("请选择输入正确的十六进制机器码"));
                    return false;
                }
                else{
                    input.push_back(mydissembler->hex2bi(lst[j]));
                    //qDebug()<<input[valid];
                    valid++;
                }
            }
        }
        return true;
    }
    else{
        QMessageBox::warning(this,tr("错误"),tr("请选择输入数据类型"));
        return false;
    }
}

void Window2::on_checkcoe_clicked(bool checked)
{
    if(checked)ui->checkseg->setChecked(0);
}

void Window2::on_checkseg_clicked(bool checked)
{
    if(checked)ui->checkcoe->setChecked(0);
}
