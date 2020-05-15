#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include<QString>
#include<QDebug>
#include<vector>
#include<cmath>
#include<QByteArray>

class Assembler
{
public:
    Assembler();
    char getType(QString);
    struct instruction{
        char type;
        QString func;
        QString valueline;
    };
    QString asm2machine(instruction);   //对asm的逐句转换
    struct label{
        QString name;
        int place;
    };
    std::vector<label>labellist;
    QString int2Binary(int,int);      //输入第一个数，输出该数的二进制code(位数由第二个输入决定）
    int hex2int(QString);               //十六进制转十进制
    int valid=0;          //有效语句条数


private:
    QString rType[17]={"add","addu","sub","subu","and",
                      "or","xor","nor","slt","sltu",
                      "sll","srl","sra","sllv","srlv",
                      "srav","jr"};
    QString iType[12]={"addi","addiu","andi","ori",
                      "xori","lui","lw","sw",
                      "beq","bne","slti","sltiu"};
    QString jType[2]={"j","jal"};
    QString regis[32]={"$zero","$at","$v0","$v1",
                      "$a0","$a1","$a2","$a3",
                      "$t0","$t1","$t2","$t3",
                      "$t4","$t5","$t6","$t7",
                      "$s0","$s1","$s2","$s3",
                      "$s4","$s5","$s6","$s7",
                      "$t8","$t9","$k0","$k1",
                      "$gp","$sp","$fp","$ra"};
    int getREGcode(QString);            //获取寄存器对应数值
    QString rTypeASM(instruction);      //r类型转换
    QString iTypeASM(instruction,int);      //i类型转换,int 有关bnq,beq
    QString jTypeASM(instruction);      //j类型转换

};

#endif // ASSEMBLER_H
