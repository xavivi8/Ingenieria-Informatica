#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripcion: Compara exactamente tres numeros recibidos por argumento. Muestr cual es el menor y si hay numeros repetidos

if [[ ${#} -ne 3 ]];then
    echo "ERROR, numero de argumentos incorrectos"
    exit
fi

for numero in "$@";do
    if ! [[ "$numero" =~ ^-?[0-9]+? ]];then
        echo "Error: '$numero' no es un numero valido"
        exit
    fi
done

mayor="$1"
menor="$1"

for numero in "$@";do
    if [[ "$numero" -gt "$mayor" ]];then
        mayor="$numero"
    fi

    if [[ "$numero" -lt "$menor" ]];then
        menor="$numero"
    fi
done

hay_repetidos=0
if [[ "$1" -eq "$2" || "$1" -eq "$3" || "$2" -eq "$3" ]];then
    hay_repetidos=1
fi

echo "Numeros introducidos: $1, $2 y $3"
echo "---------------------------------"
echo "Mayor: $mayor"
echo "Menor: $menor"

if [[ "$hay_repetidos" -eq 1 ]];then
    echo "Hay al menos dos numeros repetidos"
else
    echo "No hay ningun numero repetido"
fi