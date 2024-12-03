# Fundamentos de la programación

## Índice
- [Temario](#temario)
  - [Punteros](#punteros)

## Temario
### Punteros
# ¿Cómo funcionan los punteros en C++?

En C++, los **punteros** son una herramienta poderosa que permiten trabajar directamente con la dirección de memoria de las variables.

---

## **¿Qué es un puntero?**
Un puntero es una variable que almacena la dirección de memoria de otra variable. 

Por ejemplo, si tienes una variable `int x = 10;`, su dirección de memoria puede ser almacenada en un puntero.

---

## **Declaración de punteros**
Para declarar un puntero, se utiliza el operador `*`:

```cpp
int* ptr; // ptr es un puntero a un entero
```

---

## **¿Cómo funciona un puntero?**
1. **Asignación de dirección a un puntero:**
   Usa el operador `&` (referencia) para obtener la dirección de memoria de una variable y asignarla al puntero:

   ```cpp
   int x = 10;
   int* ptr = &x; // ptr almacena la dirección de x
   ```
2. **Acceso al valor apuntado:**
   Usa el operador `*` (desreferenciación) para acceder o modificar el valor almacenado en la dirrección que apunta el puntero:

   ```cpp
   cout << *ptr; // Muestra el valor de x (10)
   *ptr = 20;    // Cambia el valor de x a 20
   ``` 
   3. **Puntero nulo:**
   Un puntero que no apunta a ninguna dirección válida puede inicializarse como `nullptr`:

   ```cpp
   int* ptr = nullptr;
   ``` 
---
## **Ejemplo práctico:**

```cpp
#include <iostream>
using namespace std

int main() {
    int x = 10;
    int* ptr = &x; // ptr apunta a x

    cout << "Valor de x: " << x << endl;          // 10
    cout << "Dirección de x: " << &x << endl;     // Dirección de x
    cout << "Valor almacenado en ptr: " << ptr << endl;  // Dirección de x
    cout << "valor al que apunta ptr: " << *ptr << endl; // 10

    *ptr = 25;  // Cambiamos el valor de x usando el puntero
    cout << "Nuevo valor de x: " << x << endl;   // 25

    return 0;
}
```
## Salida: 
```cpp
Valor de x: 10
Dirección de x: 0x7ffee3b0
Valor almacenado en ptr: 0x7ffee3b0 
valor al que apunta ptr: 10
Nuevo valor de x: 25
```
## **Tipos especiales de punteros**
1. **Punteros constantes:**
   La dirección a la que apunta no puede cambiar:

   ```cpp
   int x = 10, y = 20;
   int* const ptr = &x; // ptr siempre apunta a x
   ```
2. **Punteros a constantes:**
   No se puede modificar el valor al que apunta:

   ```cpp
   const int x = 10;
   const int* ptr = &x;
   ```
3. **Punteros dobles:**
   Apuntan a otros punteros:

   ```cpp
   int x = 10;
   int* ptr1 = &x;
   int** ptr2 = &ptr1; // ptr2 apunta a ptr1
   ```
4. **Arreglos y punteros: **
   Los punteros y arreglos están relacionados: el nmbre del arreglo es la dirección del primer elemento.

   ```cpp
   int arr[3] = {10,20,30};
   int* ptr = arr; // ptr apunta al primer elemento
   cout << *(ptr + 1); // 20
   ```

## **Usos comunes de los punteros:**
1. **Paso de parámetros por referencia:**
   Los punteros permiten modificar el valor de las variables originales pasadas a una función.
   ```cpp
   void incrementar(int* p){
        (*p)++;
   }
   int x = 5;
   incrementar(&x);
   cout << x; // 6
   ```
1. **Gestión dinámica de memoria:**
   Los punteros se utilizan para asignar y liberar memoria dinámicamente con new y delete.
   ```cpp
   int* ptr = new int(5); // Reserva memoria para un entero
   cout << *ptr;          // 5
   delete ptr;            // Libera la memoria
   ```