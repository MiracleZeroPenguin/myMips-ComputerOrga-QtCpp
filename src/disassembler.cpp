#include "disassembler.h"

Disassembler::Disassembler()
{

}

QString Disassembler::getType(QString op){

    if(op=="000000")return "r";
    else if(op=="000010"||op=="000011")return "j";
    else{
        for(int i=0;i<12;i++){
            if(iTypeList[i].op==op)return "i";
        }
        return "error";
    }
}

QString Disassembler::getRegis(QString input){
    QString reg;
    reg=regis[binary2int(input)];
    return reg;
}

QString Disassembler::trans_rtype(QString input){
    valid++;
    QString opcode,rscode,rtcode,rdcode,shamtcode,funccode;
    QString func,rs,rt,rd,shamt;
    opcode="000000";
    rscode=input.mid(6,5);
    rtcode=input.mid(11,5);
    rdcode=input.mid(16,5);
    shamtcode=input.mid(21,5);
    funccode=input.mid(26,6);
    for(int i=0;i<17;i++){
        if(funccode==rTypeList[i].op)
            func=rTypeList[i].instruction;
    }
    if(func=="sll"||func=="srl"){
        //sll $rd,$rt,shamt
        rt=getRegis(rtcode);
        rd=getRegis(rdcode);
        shamt=QString::number(binary2int(shamtcode));
        return func+" "+rd+", "+rt+", "+shamt;
    }
    else if (func=="sra") {
        //sra $rd,$rt,shamt(signed)
        rt=getRegis(rtcode);
        rd=getRegis(rdcode);
        shamt=QString::number(binary2int_sign(shamtcode));
        return func+" "+rd+", "+rt+", "+shamt;
    }
    else if (func=="jr") {
        rs=getRegis(rscode);
        return func+" "+rs;
    }
    else{
        //func $rd,$rt,$rs
        rt=getRegis(rtcode);
        rd=getRegis(rdcode);
        rs=getRegis(rscode);
        return func+" "+rd+", "+rt+", "+rs;
    }
}

QString Disassembler::trans_jtype(QString input){
    valid++;
    QString opcode,addrcode;
    QString op;
    opcode=input.mid(0,6);
    addrcode=input.mid(6,26);
    if(opcode=="000010")op="j";
    else op="jal";

    struct label newlabel;
    newlabel.place=binary2int(addrcode);

    bool existLabel=false;
    for(int i=0;i<labellist.size();i++){
        if(labellist[i].place==newlabel.place){
            existLabel=true;
            newlabel.name=labellist[i].name;
            break;
        }
    }
    if(!existLabel){
        newlabel.name="Loop"+QString::number(labellist.size()+1);
        labellist.push_back(newlabel);
    }
    return op+" "+newlabel.name;
}

QString Disassembler::trans_itype(QString input){
    valid++;
    QString opcode,rscode,rtcode,immecode;
    QString op,rs,rt,imme;
    opcode=input.mid(0,6);
    rscode=input.mid(6,5);
    rtcode=input.mid(11,5);
    immecode=input.mid(16,16);
    for(int i=0;i<12;i++){
        if(iTypeList[i].op==opcode)
            op=iTypeList[i].instruction;
    }
    //**********************
    rs=getRegis(rscode);
    rt=getRegis(rtcode);
    imme=QString::number(binary2int_sign(immecode));
    QString ans;
    if(op=="lui"){
        //lui $rt,imme
        //imme 16进制
        imme="0x"+bi2hex(immecode);
        ans=op+" "+rt+", "+imme;
    }
    else if(op=="lw"||op=="sw"){
        //lw $rt,imme($rs)
        ans=op+" "+rt+", "+imme+"("+rs+")";
    }
    else if (op=="bne"||op=="beq") {
        // bne $rt,$rs,label
        struct label newlabel;
        newlabel.place=valid+binary2int(immecode);

        bool existLabel=false;
        for(int i=0;i<labellist.size();i++){
            if(labellist[i].place==newlabel.place){
                existLabel=true;
                newlabel.name=labellist[i].name;
                break;
            }
        }
        if(!existLabel){
            newlabel.name="Loop"+QString::number(labellist.size()+1);
            labellist.push_back(newlabel);
        }
        ans=op+" "+rt+", "+rs+", "+newlabel.name;
        return ans;
    }
    else{
        //op rt,rs,imme
        //imme>15或<-16输出十六进制
        if(imme.toInt()>15||imme.toInt()<-16){
            imme="0x"+bi2hex(immecode);
        }
        ans=op+" "+rt+", "+rs+", "+imme;
    }
    qDebug()<<ans;
    return ans;
}

QString Disassembler::bi2hex(QString in){
    int lack0=in.length()%4;
    for(int i=0;i<lack0;i++){
        in="0"+in;
    }
    QString out="";
    for(int i=0;i<in.length()/4;i++){
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

int Disassembler::binary2int_sign(QString input){
    int num=input.length();
    int ans=0;
    for(int i=1;i<num;i++){
        int bit=input.mid(i,1).toInt();
        ans=ans+(bit<<(num-i-1));
    }
    if(input.mid(0,1)=="1")
        return ans-(1<<(input.length()-1));
    else
        return ans;
}

int Disassembler::binary2int(QString input){
    int num=input.length();
    int ans=0;
    for(int i=0;i<num;i++){
        int bit=input.mid(i,1).toInt();
        ans=ans+(bit<<(num-i-1));
    }
    return ans;
}

QString Disassembler::hex2bi(QString input){
    QString ans="";
    char*  ch;
    QByteArray ba = input.toLatin1();
    ch=ba.data();
    for(int i=0;i<8;i++){
        if(ch[i]>='A'&&ch[i]<='F'){
            int a=ch[i]-'A'+10;
            switch (a) {
            case 10:ans=ans+"1010";break;
            case 11:ans=ans+"1011";break;
            case 12:ans=ans+"1100";break;
            case 13:ans=ans+"1101";break;
            case 14:ans=ans+"1110";break;
            case 15:ans=ans+"1111";break;
            }
        }
        else if (ch[i]>='a'&&ch[i]<='f') {
            int a=ch[i]-'a'+10;
            switch (a) {
            case 10:ans=ans+"1010";break;
            case 11:ans=ans+"1011";break;
            case 12:ans=ans+"1100";break;
            case 13:ans=ans+"1101";break;
            case 14:ans=ans+"1110";break;
            case 15:ans=ans+"1111";break;
            }
        }
        else if (ch[i]>='0'&&ch[i]<='9') {
            int a=ch[i]-'0';
            switch (a) {
            case 0:ans=ans+"0000";break;
            case 1:ans=ans+"0001";break;
            case 2:ans=ans+"0010";break;
            case 3:ans=ans+"0011";break;
            case 4:ans=ans+"0100";break;
            case 5:ans=ans+"0101";break;
            case 6:ans=ans+"0110";break;
            case 7:ans=ans+"0111";break;
            case 8:ans=ans+"1000";break;
            case 9:ans=ans+"1001";break;
            }
        }
        else{
            return "error";
        }
    }
    return ans;
}
