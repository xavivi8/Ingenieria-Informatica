.text
.globl main

main:
    li t0, 40
    li t1, 122

bucle:
    mv a0, t0
    li a7, 1
    ecall
    li a0, 32 #espacio
    li a7, 11
    ecall
    mv a0, t0
    li a7, 11
    ecall
    li a0, 10 #\n
    li a7, 11
    ecall
    addi t0, t0, 1
    ble t0, t1, bucle
    
fin_bucle:
    li a7, 10
    ecall