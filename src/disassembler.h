#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H
#include<QString>
#include<QDebug>
#include<vector>
#include<cmath>
#include<QByteArray>

class Disassembler
{
public:
    Disassembler();
    QString hex2bi(QString);        //16进制转换为2进制
    QString getType(QString);       //6位二进制返回i,j,r,error
    QString trans_itype(QString);   //输入32位二进制，返回对应itype指令
    QString trans_jtype(QString);   //输入32位二进制，返回对应jtype指令
    QString trans_rtype(QString);   //输入32位二进制，返回对应jtype指令
    struct label{
        int place;
        QString name;
    };
    std::vector<label>labellist;
    int valid=0;      //有效语句条数

private:
    QString regis[32]={"$zero","$at","$v0","$v1",
                      "$a0","$a1","$a2","$a3",
                      "$t0","$t1","$t2","$t3",
                      "$t4","$t5","$t6","$t7",
                      "$s0","$s1","$s2","$s3",
                      "$s4","$s5","$s6","$s7",
                      "$t8","$t9","$k0","$k1",
                      "$gp","$sp","$fp","$ra"};
    /**************itype*************/
    struct iType{
      QString op;
      QString instruction;
    };
    struct iType iTypeList[12]={"001000","addi","001001","addiu","001100","andi","001101","ori",
                                "001110","xori","001111","lui","100011","lw","101011","sw",
                                "000100","beq","000101","bne","001010","slti","001011","sltiu"};
    struct iType rTypeList[17]={"100000","add","100001","addu","100010","sub","100011","subu",
                               "100100","and","100101","or","100110","xor","100111","nor",
                               "101010","slt","101011","sltu","000000","sll","000010","srl",
                               "000011","sra","000100","sllv","000110","srlv","000111","srav",
                               "001000","j"};
    QString getRegis(QString);  //从5位2进制返回寄存器名称
    int binary2int_sign(QString); //n位二进制转十进制(有符号)
    int binary2int(QString);       //n位二进制转十进制(无符号）
    QString bi2hex(QString);        //2进制转16进制
    QString Hex[16] = {
        "0","1","2","3",
        "4","5","6","7",
        "8","9","A","B",
        "C","D","E","F"
    };
};

#endif // DISASSEMBLER_H
