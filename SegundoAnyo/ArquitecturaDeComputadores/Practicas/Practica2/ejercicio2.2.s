.text
.globl main

main:
    li a0, 0
    li t0, 1
    li t1, 1000
bucle:
    add a0, a0, t0
    addi t0, t0, 2
    ble t0, t1, bucle
    
fin_bucle:
    li a7, 1
    ecall
    li a7, 10
    ecall