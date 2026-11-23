#!/bin/bash
# Autora: Lina Gracia-Cabrera
# Descripcion: Escribe texto con y sin saltos de lineas y con tabulaciones
echo -n "Imprimiendo texto sin nueva linea"
echo "Imprimiendo texto con nueva linea"
echo -e "\nInterpretacion \t Caracteres \t Tabulador \n"
echo "\nNo Interpretacion \t  Caracteres \t Tabuladores\n"
#mostrar los parámetros de entrada con tabulador
echo -e "\nLos 3 prarametros de entrada son \t$1 \t$2 \t$3\n"
