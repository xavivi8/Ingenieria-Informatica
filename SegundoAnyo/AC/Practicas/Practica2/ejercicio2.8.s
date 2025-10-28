.data

vec:
    .word 7,4,23,12,6,20,17,8,3,10
msgMin:
    .string "Min: "
msgMax:
    .string "Max: "
nl:
    .string "\n"
    
.text
.globl main

main:
    la    t0, vec          # t0 = &vec[0]
    lw    t2, 0(t0)        # t2 = vec[0]
    mv    a0, t2           # a0 = min
    mv    a1, t2           # a1 = max
    addi  t0, t0, 4        # avanzar al segundo
    li    t1, 9            # quedan 9 elementos por procesar

bucle:
    lw    t2, 0(t0)        # cargar siguiente valor

    blt   t2, a0, set_min

skip_min:
    blt   a1, t2, set_max

skip_max:
    addi  t0, t0, 4        # siguiente elemento
    addi  t1, t1, -1       # quedan--
    bnez  t1, bucle        # repetir mientras queden

    mv    t5, a0           # backup min
    mv    t6, a1           # backup max

    # Imprimir Min
    la    a0, msgMin
    li    a7, 4
    ecall
    mv    a0, t5
    li    a7, 1
    ecall
    la    a0, nl
    li    a7, 4
    ecall

    # Imprimir Max
    la    a0, msgMax
    li    a7, 4
    ecall
    mv    a0, t6
    li    a7, 1
    ecall
    la    a0, nl
    li    a7, 4
    ecall

    # Restaurar a0/a1 como pide el enunciado
    mv    a0, t5           # a0 = min
    mv    a1, t6           # a1 = max

    li    a7, 10           # salir
    ecall

set_min:
    mv    a0, t2
    j     skip_min

set_max:
    mv    a1, t2
    j     skip_max