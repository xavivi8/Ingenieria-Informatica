# Análisis de tablas de dispersión

* *Francisco Javier Martín-Lunas Escobar*

## Tamaño de tabla: 5099
| función | máximo de colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:---------------:|:----------------------:|
| hash1   |  36          |      0.649147       |        1.38852         |
| hash2   |  12          |      0.649147       |        0.729607         |
| hash3   |  11          |      0.649147       |        0.524773         |

Número de inserciones con más de 10 colisiones para este tamaño de tabla:

- hash1: 89
- hash2: 2
- hash3: 1

## Tamaño de tabla: 4871
| función | máximo de colisiones | factor de carga | promedio de colisiones |
|---------|:--------------------:|:---------------:|:----------------------:|
| hash1   |  43          |      0.679532       |        1.35408         |
| hash2   |  14          |      0.679532       |        0.808459         |
| hash3   |  12          |      0.679532       |        0.581873         |

Número de inserciones con más de 10 colisiones para este tamaño de tabla:

- hash1: 74
- hash2: 4
- hash3: 3

## Justificación de la configuración elegida

Hemos optado por la configuración de tabla con tamaño 5099, aplicando la función hash3 con λ objetivo 0.65.
Es la que ofrece el menor promedio de colisiones (0.524773) y un máximo de 11 colisiones en la inserción más costosa,
además de un número de inserciones con más de 10 colisiones igual a 1, inferior al de otras alternativas.

## Comparación de tiempos dados en milisegundos

Tiempo en realizar las búsquedas en la Tabla Hash: 0.719 ms
Tiempo en realizar las búsquedas en la Lista: 43.9028 ms
Tiempo aproximado de carga de datos y construcción de la tabla: 44.6336 ms
