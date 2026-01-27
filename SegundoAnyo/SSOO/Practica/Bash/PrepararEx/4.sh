#!/bin/bash
#Autor: F
#Descripcion: 

if ! [[ ${#} -ne 1 ]];then
    ruta=$1

    if [[ -e "$ruta" ]];then
        echo "El archivo $ruta existe"
        if [[ -O "ruta" ]];then
            echo "El archivo $ruta es propidad del usuario que ejecuta el script"
        else
            echo "El archivo $ruta no es propidad del usuario que ejecuta el script"
        fi

        if [[ -x "$ruta" ]];then
            echo "El archivo tiene permisos de ejecucion"
        else
            echo "El archivo no tiene permisos de ejecucion"
        fi
    else
        echo "El archivo $ruta no existe"
    fi
else
    echo "ERROR, numero de argumentos incorrectos"
    echo "Uso: $0 ruta"
fi