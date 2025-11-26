# 📦 Proyecto: Practica2Listas

Este proyecto está organizado en varias carpetas que separan las cabeceras, implementaciones, datos y archivos de compilación, facilitando la modularidad y el mantenimiento del código.

## 🗂️ Estructura del proyecto

```
Practica5Hashing/
│
├── include/                # Archivos de cabecera (.h)
│   ├── Farmacia.h
│   ├── Laboratorio.h
│   ├── MediExpress.h
│   ├── PaMedicamento.h
│   ├── Stock.h
│   ├── THashMedicam.h
│   └── utils.h
│
├── src/                    # Implementaciones (.cpp y .tpp)
│   ├── Farmacia.cpp
│   ├── Laboratorio.cpp
│   ├── main.cpp
│   ├── MediExpress.h
│   ├── PaMedicamento.h
│   ├── Stock.h
│   ├── THashMedicam.h
│   └── Stock.cpp            # Punto de entrada del programa
│
├── data/                   # Archivos de datos de prueba
│   ├── pa_medicamentos.csv
│   ├── farmacias.csv
│   └── laboratorios.csv
│
├── Makefile                # (Opcional) Compilación automática
├── analisis_Thash.md       # Analisis de hash 
└── CMakeLists.txt          # Configuración para CMake
```

## 📁 Descripción de carpetas

- **`include/`** → Cabeceras con definiciones de clases y funciones.
- **`src/`** → Implementaciones en C++.
- **`data/`** → Archivos CSV de prueba.
- **`Makefile` / `CMakeLists.txt`** → Archivos para automatizar la compilación.
