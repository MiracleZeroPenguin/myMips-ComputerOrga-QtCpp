j start
add $zero, $zero, $zero
add $zero, $zero, $zero
add $zero, $zero, $zero
add $zero, $zero, $zero
add $zero, $zero, $zero
add $zero, $zero, $zero
add $zero, $zero, $zero
start:
lui $v1, 0xf000
sll $a0, $v1, 1
//替换掉lui $a0, 0xe000
lui $t0, 0x8000
addi $s4, $zero, 0x003f
srl $a2, $t0, 4
add $a2, $a2, $v1
//以上两条替换掉lui $a2, 0xf800
nor $at, $zero, $zero//r1=0xffffffff
slt $v0, $at, $zero//r2=1
addi $t2, $at, -1//r10=0xfffffffe

sw $a2, 4($v1)//计数端口送常数r6=0xf8000000
lw $a1, ($v1)//读取GPIO端口状态
add $a1, $a1, $a1
add $a1, $a1, $a1
sw $a1, ($v1)
addi $t1, $t1, 1
sw $t1, ($a0)
lw $t5, 20($zero)

loop2:
lw $a1, ($v1)
add $a1, $a1, $a1
add $a1, $a1, $a1
sw $a1, ($v1)
lw $a1, ($v1)
and $t3, $a1, $t0
addi $t5, $t5, 1
bne $t5, $zero, l_next
jal C_init
l_next:
lw $a1, ($v1)
addi $s2, $zero, 8
add $s6, $s2, $s2
add $s2, $s2, $s6
and $t3, $a1, $s2
beq $t3, $zero, L00
beq $t3, $s2, L11
addi $s2, $zero, 8
beq $t3, $s2, L01
sw $t1, ($a0)
j loop2
L00:
bne $t2, $at, L3
nor $t2, $zero, $zero
add $t2, $t2, $t2
L3:
sw $t2, ($a0)
j loop2
L11:
lw $t1, 96($s1)
sw $t1, ($a0)
j loop2
L01:
lw $t1, 32($s1)
sw $t1, ($a0)
j loop2

C_init:
lw $t5, 20($zero)
add $t2, $t2, $t2
ori $t2, $t2, 1
addi $s1, $s1, 4
and $s1, $s1, $s4
add $t1, $t1, $v0
bne $t1, $at, L7
addi $t1, $t1, 5

L7:
lw $a1, ($v1)
add $t3, $a1, $a1
add $t3, $t3, $t3
sw $t3, ($v1)
sw $a2, 4($v1)
jr $ra
