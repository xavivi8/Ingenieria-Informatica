#factorial(n)
#Entrada: a0=n
#Salida: a1=n! 

li a0, 5
call factorial

li a7, 10
ecall

factorial:
    addi sp, sp, -16 #Reserba 16 bytes (stack frame alineado)
    sw ra, 0(sp) #Guardar dirección de retorno
    sw a0, 4(sp) #Guardar parámetro n
    
    addi a0, a0, -1 #n=n-1
    bnez a0, recurse #if(n!=0)-> llamada recursiva
    li a1, 1 #caso base: factorial(0)=1
    j end

recurse: 
    call factorial #llamada recursiva

end:
    lw a0, 4(sp) #recuperar anterior
    mul a1, a1, a0 #a1=a1*n
    lw ra, 0(sp) #recuperar dirección de retorno
    addi sp, sp, 16 #liberar stack frame
    ret #volver a la función que llamó