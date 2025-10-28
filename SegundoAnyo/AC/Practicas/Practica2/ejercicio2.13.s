    .data
mat:    .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
m00:    .string "A[0,0]: "
m11:    .string "A[1,1]: "
m22:    .string "A[2,2]: "
m33:    .string "A[3,3]: "
nl:     .string "\n"

    .text
    .globl main
main:
    # (0,0)
    li    a1, 0
    li    a2, 0
    call  get_at          # a0 = valor
    mv    t2, a0          # GUARDAR valor
    la    a0, m00         # imprimir etiqueta
    li    a7, 4
    ecall
    mv    a0, t2          # recuperar valor
    li    a7, 1
    ecall
    la    a0, nl
    li    a7, 4
    ecall

    # (1,1)
    li    a1, 1
    li    a2, 1
    call  get_at
    mv    t2, a0
    la    a0, m11
    li    a7, 4
    ecall
    mv    a0, t2
    li    a7, 1
    ecall
    la    a0, nl
    li    a7, 4
    ecall

    # (2,2)
    li    a1, 2
    li    a2, 2
    call  get_at
    mv    t2, a0
    la    a0, m22
    li    a7, 4
    ecall
    mv    a0, t2
    li    a7, 1
    ecall
    la    a0, nl
    li    a7, 4
    ecall

    # (3,3)
    li    a1, 3
    li    a2, 3
    call  get_at
    mv    t2, a0
    la    a0, m33
    li    a7, 4
    ecall
    mv    a0, t2
    li    a7, 1
    ecall
    la    a0, nl
    li    a7, 4
    ecall

    li    a7, 10
    ecall

# get_at(a1=fila, a2=col) -> a0
get_at:
    slli  t0, a1, 2       # fila * 4 (en palabras)
    add   t0, t0, a2      # fila*4 + col
    slli  t0, t0, 2       # *4 bytes
    la    t1, mat
    add   t1, t1, t0
    lw    a0, 0(t1)
    ret