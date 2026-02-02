# 📦 Proyecto: Practica2Listas

Este proyecto está organizado en varias carpetas que separan las cabeceras, implementaciones, datos y archivos de compilación, facilitando la modularidad y el mantenimiento del código.

## 🗂️ Estructura del proyecto

```
Practica2Listas/
│
├── include/                # Archivos de cabecera (.h)
│   ├── MediExpress.h
│   ├── PaMedicamento.h
│   ├── Laboratorio.h
│   ├── VDinamico.h
│   ├── utils.h
│   └── ListaEnlazada.h
│
├── src/                    # Implementaciones (.cpp y .tpp)
│   ├── MediExpress.cpp
│   ├── PaMedicamento.cpp
│   ├── VDinamico.tpp
│   ├── ListaEnlazada.tpp
│   ├── Laboratorio.cpp
│   ├── utils.cpp
│   └── main.cpp            # Punto de entrada del programa
│
├── data/                   # Archivos de datos de prueba
│   ├── pa_medicamentos.csv
│   ├── farmacias.csv
│   └── laboratorios.csv
│
├── Makefile                # (Opcional) Compilación automática
└── CMakeLists.txt          # Configuración para CMake
```

## 📁 Descripción de carpetas

- **`include/`** → Cabeceras con definiciones de clases y funciones.
- **`src/`** → Implementaciones en C++.
- **`data/`** → Archivos CSV de prueba.
- **`Makefile` / `CMakeLists.txt`** → Archivos para automatizar la compilación.
