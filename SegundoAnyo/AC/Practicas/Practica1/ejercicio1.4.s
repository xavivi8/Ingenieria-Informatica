addi a0, zero, 23
addi a1, zero, 4
div t0, a0, a1
rem t1, a0, a1
mv a0, t0
addi a7, zero, 1
ecall
mv a0, t1
ecall