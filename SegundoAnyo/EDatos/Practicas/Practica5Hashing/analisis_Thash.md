# Análisis de tablas de dispersión

* *Francisco Javier Martín-Lunas Escobar*

## Tamaño de tabla: 5099
| función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| hash1   |  38          |      89       |        0.649147       |        1.39607         |
| hash2   |  13          |      3       |        0.649147       |        0.765861         |
| hash3   |  12          |      1       |        0.649147       |        0.544713         |

Número de inserciones con más de 10 colisiones para este tamaño de tabla:

- hash1: 89
- hash2: 3
- hash3: 1

## Tamaño de tabla: 4871
| función | máximo de colisiones | supera 10 colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:--------------------:|:---------------:|:----------------------:|
| hash1   |  43          |      87       |        0.679532       |        1.36737         |
| hash2   |  14          |      6       |        0.679532       |        0.830816         |
| hash3   |  13          |      3       |        0.679532       |        0.593656         |

Número de inserciones con más de 10 colisiones para este tamaño de tabla:

- hash1: 87
- hash2: 6
- hash3: 3

## Justificación de la configuración elegida

Hemos optado por la configuración de tabla con tamaño 5099, aplicando la función hash3 con λ objetivo 0.65.
Es la que ofrece el menor promedio de colisiones (0.544713) y un máximo de 12 colisiones en la inserción más costosa,
además de un número de inserciones con más de 10 colisiones igual a 1, inferior al de otras alternativas.

## Comparación de tiempos dados en milisegundos

Tiempo en realizar las búsquedas en la Tabla Hash: 0.4461 ms
Tiempo en realizar las búsquedas en la Lista: 56.6172 ms
Tiempo aproximado de carga de datos y construcción de la tabla: 45.5163 ms
