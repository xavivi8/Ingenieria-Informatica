.text
.globl main

main:
    
    li s0, -1    # s0 = i contador exterior
    li t0, 10    # limite del bucle exterior
    li t1, 10    # limite del bucle interior

bucle_exterior:
    addi s0, s0, 1  
    li s1, -1    # s1 = j contador interior

    
bucle_interior:
    addi s1, s1, 1
    
    #imprimo el valor de s0
    mv a0, s1
    li a7, 1
    ecall
    
    #imprimo la x
    li a0, 120
    li a7, 11    
    ecall
    
    #imprimo el valor de s0
    mv a0, s0
    li a7, 1
    ecall
    
    #imprimo el
    li a0, 61
    li a7, 11
    ecall
