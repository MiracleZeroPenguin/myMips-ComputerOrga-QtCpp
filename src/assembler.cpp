#include "assembler.h"

Assembler::Assembler()
{

}

char Assembler::getType(QString name){
    for(int i=0;i<17;i++){
        if(rType[i]==name)return 'r';
    }
    for(int i=0;i<12;i++){
        if(iType[i]==name)return 'i';
    }
    for(int i=0;i<2;i++){
        if(jType[i]==name)return 'j';
    }
    return 'x';//illegal
}


QString Assembler::asm2machine(instruction input){
    if(input.type=='r'){
        valid++;
        return rTypeASM(input);
    }
    else if(input.type=='i'){
        valid++;
        return iTypeASM(input,valid);
    }
    else if(input.type=='j'){
        valid++;
        return jTypeASM(input);
    }
    else {
        return "error";
    }
}

QString Assembler::rTypeASM(instruction input){
    QList<QString>value;
    value=input.valueline.split(",");

    QList<QString>tmp;
    int valuenum=value.size();
    tmp=value[valuenum-1].split("//");
    value[valuenum-1]=tmp[0];

    QString op,rs,rt,rd,shamt,func;
    op="000000";
    if(input.func=="sll"||input.func=="srl"||input.func=="sra"){
        rs="00000";
        rt=int2Binary(getREGcode(value[1]),5);
        rd=int2Binary(getREGcode(value[0]),5);
        shamt=int2Binary(value[2].toInt(),5);
        if(input.func=="sll")func=int2Binary(0,6);
        else if(input.func=="srl")func=int2Binary(2,6);
        else func=int2Binary(3,6);
    }
    else if(input.func=="jr"){
        rs=int2Binary(getREGcode(value[0]),5);
        rt="00000";
        rd="00000";
        shamt="00000";
        func="001000";
    }
    else{
        rs=int2Binary(getREGcode(value[1]),5);
        rt=int2Binary(getREGcode(value[2]),5);
        rd=int2Binary(getREGcode(value[0]),5);
        shamt="00000";
        if(input.func=="add")
            func="100000";
        else if(input.func=="addu")
            func="100001";
        else if(input.func=="sub")
            func="100010";
        else if(input.func=="subu")
            func="100011";
        else if(input.func=="and")
            func="100100";
        else if(input.func=="or")
            func="100101";
        else if(input.func=="xor")
            func="100110";
        else if(input.func=="nor")
            func="100111";
        else if(input.func=="slt")
            func="101010";
        else if(input.func=="sltu")
            func="101011";
        else if(input.func=="sllv")
            func="000100";
        else if(input.func=="srlv")
            func="000110";
        else if(input.func=="srav")
            func="000111";
    }
    return op+rs+rt+rd+shamt+func;
}

QString Assembler::iTypeASM(instruction input,int k){
    QList<QString>value;
    QString op,rs,rt,imme;
    value=input.valueline.split(",");

    QList<QString>tmp;
    int valuenum=value.size();
    tmp=value[valuenum-1].split("//");
    value[valuenum-1]=tmp[0];

    if(value[1].mid(0,1)=="(")
        value[1]="0"+value[1];
    if(input.func=="lui"){
        op="001111";
        rs="00000";
        rt=int2Binary(getREGcode(value[0]),5);
        int tmp;
        if(value[1].mid(0,2)=="0x")
            tmp=hex2int(value[1]);
        else tmp=value[1].toInt();
        imme=int2Binary(tmp,16);
    }
    else if(input.func=="lw"||input.func=="sw"){
        if(input.func=="lw")
            op="100011";
        else op="101011";
        rt=int2Binary(getREGcode(value[0]),5);
        QList<QString>tmp;
        tmp=value[1].split("(");
        imme=int2Binary(tmp[0].toInt(),16);
        tmp[1]=tmp[1].mid(0,tmp[1].length()-1);
        rs=int2Binary(getREGcode(tmp[1]),5);
    }
    else if(input.func=="bne"||input.func=="beq"){
        if(input.func=="bne")op="000101";
        else op="000100";
        rt=int2Binary(getREGcode(value[0]),5);
        rs=int2Binary(getREGcode(value[1]),5);

        char*  s;
        QByteArray ba = value[2].toLatin1(); // must
        s=ba.data();
        if(value[2].mid(0,2)=="0x"){
            imme=int2Binary(hex2int(value[2]),16);
        }
        else if(s[0]<='9'&&s[0]>='0'){
            imme=int2Binary(value[2].toInt(),16);
        }
        else{
            for(int i=0;i<labellist.size();i++){
                if(value[2]==labellist[i].name){

                    //*****************************************
                    imme=int2Binary(labellist[i].place-k,16);
                }
            }
        }

    }
    else{
        rt=int2Binary(getREGcode(value[0]),5);
        rs=int2Binary(getREGcode(value[1]),5);
        if(value[2].mid(0,2)=="0x"){
            imme=int2Binary(hex2int(value[2]),16);
        }
        else{
            imme=int2Binary(value[2].toInt(),16);
        }
        /*"addi","addiu","andi","ori",
                      "xori","slti","sltiu"*/
        if(input.func=="addi")op="001000";
        else if(input.func=="addiu")op="001001";
        else if(input.func=="andi")op="001100";
        else if(input.func=="ori")op="001101";
        else if(input.func=="xori")op="001110";
        else if(input.func=="slti")op="001010";
        else if(input.func=="sltiu")op="001011";
    }
    return op+rs+rt+imme;
}

QString Assembler::jTypeASM(instruction input){
    QList<QString>tmp;
    tmp=input.valueline.split("//");
    QString imme=tmp[0];

    QString op,addr;
    if(input.func=="j")op="000010";
    else op="000011";
    //get addr
    char*  s;
    QByteArray ba = imme.toLatin1(); // must
    s=ba.data();
    if(imme.mid(0,2)=="0x"){
        addr=int2Binary(hex2int(imme),26);
    }
    else if(s[0]<='9'&&s[0]>='0'){
        addr=int2Binary(imme.toInt(),26);
    }
    else{
        for(int i=0;i<labellist.size();i++){
            if(imme==labellist[i].name)
                addr=int2Binary(labellist[i].place,26);
        }
    }
    return op+addr;
}

int Assembler::hex2int(QString hex){
    char*  s;
    QByteArray ba = hex.toLatin1(); // must
    s=ba.data();
    int count=hex.length();
    int sum=0;
    for(int i=count-1;i>=2;i--)//从十六进制个位开始，每位都转换成十进制
    {
        if(s[i]>='0'&&s[i]<='9')//数字字符的转换
        {
            sum+=(s[i]-48)*pow(16,count-i-1);
        }
        else if(s[i]>='A'&&s[i]<='F')//字母字符的转换
        {
            sum+=(s[i]-55)*pow(16,count-i-1);
        }
        else if(s[i]>='a'&&s[i]<='f'){
            s[i]=std::toupper(s[i]);
            sum+=(s[i]-55)*pow(16,count-i-1);
        }
    }
    return sum;
}

int Assembler::getREGcode(QString r){
    for(int i=0;i<32;i++){
        if(regis[i]==r)
            return i;
    }
    return 32;
}

QString Assembler::int2Binary(int input,int num){
    if(input>=0){
        QString ans="";
        for(int i=0;i<num;i++){
            int bit=input%2;
            ans=QString::number(bit)+ans;
            input=input/2;
        }
        return ans;
    }
    else{
        input=pow(2,num)+input;
        QString ans="";
        for(int i=0;i<num;i++){
            int bit=input%2;
            ans=QString::number(bit)+ans;
            input=input/2;
        }
        return ans;
    }

}
