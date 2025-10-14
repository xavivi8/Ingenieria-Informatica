.data

vec:
    .word 7,4,23,12,6,20,17,8,3,10
msgM:
    .string "Suma impares: "
nl:
    .string "\n"
    
.text
.globl main

main:
    la t0, vec
    li t1, 10
    li s0,0

bucle:
    lw t2, 0(t0)
    andi t3, t2,1
    beqz t3, salto
    add s0, s0,t2

salto:
    addi t0, t0, 4
    addi t1,t1,-1
    bnez t1, bucle
    
    la a0, msgM
    li a7, 4
    ecall
    mv    a0, s0 
    li    a7, 1
    ecall
    la    a0, nl
    li    a7, 4
    ecall
    li    a7, 10
    ecall