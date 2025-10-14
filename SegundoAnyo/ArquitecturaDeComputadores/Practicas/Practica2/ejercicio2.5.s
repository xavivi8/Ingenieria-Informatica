.data

vec:
    .word 7,4,23,12,6,20,17,8,3,10
msgM:
    .string "Media: "
nl:
    .string "\n"
    
.text
.globl main

main:
    la t0, vec
    li t1, 10
    li s0, 0 #suma
    li s1, 0 #contador

bucle:
    lw t2, 0 t0
    add s0, s0, t2
    addi s1, s1, 1
    addi t0, t0, 4
    addi t1, t1, -1
    bnez t1, bucle
    
    div t3, s0, s1
    la a0, msgM
    li a7,4
    ecall
    mv a0, t3
    li a7,1
    ecall
    la a0,nl
    li a7,4
    ecall
    li a7,10
    ecall