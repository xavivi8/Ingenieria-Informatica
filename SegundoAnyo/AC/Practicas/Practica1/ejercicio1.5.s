.data
num1: .word 10
num2: .word 20
num3: .word 30
.text
main:
    addi a0, zero, 0
    lw t0, num1
    add a0, a0, t0
    lw t0, num2
    add a0, a0, t0
    lw t0, num3
    add a0, a0, t0
    addi a7, zero, 1
    ecall