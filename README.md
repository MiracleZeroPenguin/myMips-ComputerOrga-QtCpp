# README



## 功能描述

1. 输入MIPS汇编程序，返回对应16进制机器码
2. 输入MIPS 16进制机器码，返回对应汇编程序
3. 支持31条MIPS指令，包括

| 序号   | 符号  | 示例            | 解释                                  |
| ------ | ----- | --------------- | ------------------------------------- |
| R-type |       |                 |                                       |
| 1      | add   | add $1,$2,$3    | $1=$2+$3                              |
| 2      | addu  | addu $1,$2,$3   | $1=$2+$3无符号数                      |
| 3      | sub   | sub $1,$2,$3    | $1=$2-$3                              |
| 4      | subu  | subu $1,$2,$3   | $1=$2-$3无符号数                      |
| 5      | and   | and $1,$2,$3    | $1=$2 & $3                            |
| 6      | or    | or $1,$2,$3     | $1=$2                                 |
| 7      | xor   | xor $1,$2,$3    | $1=$2 ^ $3                            |
| 8      | nor   | nor $1,$2,$3    | $1=~($2\|$3)                          |
| 9      | slt   | slt $1,$2,$3    | if($2<$3)  $1=1 else  $1=0            |
| 10     | sltu  | sltu $1,$2,$3   | if($2<$3)  $1=1 else  $1=0无符号数    |
| 11     | sll   | sll $1,$2,10    | $1=$2<<10                             |
| 12     | srl   | srl $1,$2,10    | $1=$2>>10                             |
| 13     | sra   | sra $1,$2,10    | $1=$2>>10                             |
| 14     | sllv  | sllv $1,$2,$3   | $1=$2<<$3                             |
| 15     | srlv  | srlv $1,$2,$3   | $1=$2>>$3                             |
| 16     | srav  | srav $1,$2,$3   | $1=$2>>$3                             |
| 17     | jr    | jr $31          | goto $31                              |
| I-type |       |                 |                                       |
| 18     | addi  | addi $1,$2,100  | $1=$2+100                             |
| 19     | addiu | addiu $1,$2,100 | $1=$2+100无符号数                     |
| 20     | andi  | andi $1,$2,10   | $1=$2 & 10                            |
| 21     | ori   | ori $1,$2,10    | $1=$2\|10                             |
| 22     | xori  | xori $1,$2,10   | $1=$2 ^ 10                            |
| 23     | lui   | lui $1,100      | \$1=100*65536                          |
| 24     | lw    | lw $1,10($2)    | $1=memory[$2+10]                      |
| 25     | sw    | sw $1,10($2)    | memory[$2+10]=$1                      |
| 26     | beq   | beq $1,$2,10    | if($1==$2) goto PC+4+40 支持label跳转 |
| 27     | bne   | bne $1,$2,10    | if($1!=$2) goto PC+4+40 支持label跳转 |
| 28     | slti  | slti $1,$2,10   | if($2<10) $1=1 else $1=0              |
| 29     | sltiu | sltiu $1,$2,10  | if($2<10) $1=1 else $1=0              |
| J-type |       |                 | 也支持label跳转                       |
| 30     | j     | j 10000         | goto 10000                            |
| 31     | jal   | jal 10000       | $31<-PC+4; goto 10000                 |



## 开发环境

64位 Windows 10

64位 MinGW 7.3.0

32位 Qt 5.13.0

32位 Qt Creator 4.9.1(Enterprise)



## 项目结构简介

- newMips											     | 源文件
  - newMips.pro							          | Qt Creator 工程文件
    - *.ui										        | Qt界面
    - *.h										         | 头文件
    - *.cpp								 	        | cpp
    - img.ico+icoimg.rc		                | 图标
- newMips_demo						  	    	| 可执行文件+驱动
  - newMips.exe							         | release版本可执行文件
  - *.dll										     	  | 附带驱动
  - *.file								                  | 其他附属文件



## 测试DEMO

- 汇编
  - scpu_demo_2018.txt
  - scpu_demo_2018.asm
- 反汇编
  - scpu_demo_2018.coe
  - scpu_demo_2018.txt



## 作者版权

​	Copyright(C) 2020-2021 Miracle_Zero

​	All rights reserved\n\nfilename:	newMips

​	description:	  用于<u>计算机组成</u>课程的课程作业

​						     实现asm汇编码向16进制coe机器码的汇编转换

​						     实现16进制coe机器码向asm汇编码的反汇编转换

​	created by 卢佳盈 at 2020/05/06

​	浙江大学计算机科学与技术学院



## 版本

1.0.0 released at 2020/5/6



## 联系方式

email：	ljy28501@163.com
