A = [
    [1, 2, 3],
    [4, 5, 6]
]

B = [
    [-1, 0],
    [ 0, 1],
    [ 1, 1]
]

filas_A = len(A)
cols_A = len(A[0])
filas_B = len(B)
cols_B = len(B[0])

if cols_A != filas_B:
    print("Error: No se pueden multiplicar (dimensiones incompatibles).")
else:
    resultado = []
    for i in range(filas_A):
        fila = []
        for j in range(cols_B):
            suma = 0
            for k in range(cols_A):
                suma += A[i][k] * B[k][j]
            fila.append(suma)
        resultado.append(fila)

    print("El producto de las matrices A y B es:", resultado)
