.data
num:
    .word 75000
.text
main:
    lw a0, num
    addi a7, zero, 1
    ecall