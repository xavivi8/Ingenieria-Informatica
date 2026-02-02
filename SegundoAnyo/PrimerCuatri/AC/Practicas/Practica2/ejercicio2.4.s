.text
.globl main

main:
    
    li s0, -1    # s0 = i contador exterior
    li t0, 10    # limite del bucle interno

bucle_exterior:
    addi s0, s0, 1  
    bgt s0, t0, fin
    li s1, -1    # s1 = j contador interior
    
    li a0, 10
    li a7, 11
    ecall

    
bucle_interior:
    addi s1, s1, 1
    
    #imprimo el valor de s1
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
    
    #imprimo el =
    li a0, 61
    li a7, 11
    ecall
    
    mul t1, s1, s0  # t0 = s1 * s0
    mv a0, t1
    li a7, 1
    ecall
    
    #imprimo el _
    li a0, 95
    li a7, 11
    ecall
    
    blt s1, t0, bucle_interior
    beq s1, t0, bucle_exterior

fin:
    li a7, 10
    ecall