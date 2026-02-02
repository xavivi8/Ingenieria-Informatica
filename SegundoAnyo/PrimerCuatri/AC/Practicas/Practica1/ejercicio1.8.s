.data
resultado:
    .word 0
    .word 0
.text
main:
    addi a0, zero, 23
    addi a1, zero, 4
    div t0, a0, a1
    rem t1, a0, a1
    la t2, resultado
    sw t0, 0(t2)
    sw t1, 4(t2)
    