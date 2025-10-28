.data
nums: 
    .word 10 
    .word 20
    .word 30
.text
main:
    addi a0, zero, 0
    la t0, nums
    lw t1, 0(t0)
    add a0, a0, t1
    lw t1, 4(t0)
    add a0, a0, t1
    lw t1, 8(t0)
    add a0, a0, t1
    addi a7, zero, 1
    ecall