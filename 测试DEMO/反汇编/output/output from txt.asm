j Loop1
add $zero, $zero, $zero
add $zero, $zero, $zero
add $zero, $zero, $zero
add $zero, $zero, $zero
add $zero, $zero, $zero
add $zero, $zero, $zero
add $zero, $zero, $zero

Loop1:
lui $v1, 0xF000
sll $a0, $v1, 1
lui $t0, 0x8000
addi $s4, $zero, 0x003F
srl $a2, $t0, 4
add $a2, $v1, $a2
nor $at, $zero, $zero
slt $v0, $zero, $at
addi $t2, $at, -1
sw $a2, 4($v1)
lw $a1, 0($v1)
add $a1, $a1, $a1
add $a1, $a1, $a1
sw $a1, 0($v1)
addi $t1, $t1, 1
sw $t1, 0($a0)
lw $t5, 20($zero)

Loop7:
lw $a1, 0($v1)
add $a1, $a1, $a1
add $a1, $a1, $a1
sw $a1, 0($v1)
lw $a1, 0($v1)
and $t3, $t0, $a1
addi $t5, $t5, 1
bne $zero, $t5, Loop2
jal Loop3

Loop2:
lw $a1, 0($v1)
addi $s2, $zero, 8
add $s6, $s2, $s2
add $s2, $s6, $s2
and $t3, $s2, $a1
beq $zero, $t3, Loop4
beq $s2, $t3, Loop5
addi $s2, $zero, 8
beq $s2, $t3, Loop6
sw $t1, 0($a0)
j Loop7

Loop4:
bne $at, $t2, Loop8
nor $t2, $zero, $zero
add $t2, $t2, $t2

Loop8:
sw $t2, 0($a0)
j Loop7

Loop5:
lw $t1, 96($s1)
sw $t1, 0($a0)
j Loop7

Loop6:
lw $t1, 32($s1)
sw $t1, 0($a0)
j Loop7

Loop3:
lw $t5, 20($zero)
add $t2, $t2, $t2
ori $t2, $t2, 1
addi $s1, $s1, 4
and $s1, $s4, $s1
add $t1, $v0, $t1
bne $at, $t1, Loop9
addi $t1, $t1, 5

Loop9:
lw $a1, 0($v1)
add $t3, $a1, $a1
add $t3, $t3, $t3
sw $t3, 0($v1)
sw $a2, 4($v1)
j $zero, $zero, $ra
