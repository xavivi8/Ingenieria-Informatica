.data

matriz:
    .word 1,2,3,4
    .word 5,6,7,8
    .word 9,10,11,12
    .word 13,14,15,16
salto:
    .string "\n"
    
.text
.globl main

main:
    la t0, matriz
    li t1, 4
    li t2, 4
    li t3, 0

bucleExterno:
    beq t1,t3,fin
    li t4,0
    li t5,0

bucleInterno:
    beq t5,t2, finFila
    
    lw t6,0(t0)
    add t4,t4,t6
    addi t0,t0,4
    addi t5,t5,1
    j bucleInterno
    
finFila:
    mv a0,t5
    mv a0, t4
    li a7, 1
    ecall

    la a0, salto
    li a7, 4
    ecall

    addi t3, t3, 1
    j bucleExterno
    
fin:
    li a7, 10
    ecall