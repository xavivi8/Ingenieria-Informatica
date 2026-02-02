#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripción:

if [[ ${#} -gt 3 ]];then
    base=$HOME
    if [[ -e $base ]];then
        if [[ -x $base ]];then
            count=0
            for (( $i = 4; i<=${#};i++));do
                if [[ -d ${!i} ]];then
                    if [[ -r ${!i} ]];then
                        if [[ -x ${!i} ]];then 
                            ls ${!i} > tmp 2>/dev/null
                            while read linea; do
                                echo
                            done < tmp
                            rm tmp
                        else
                            echo "El directorio ${!i} no tiene permisos de ejecucion"
                        fi
                    else
                        echo "El directorio ${!i} no tiene permisos de lectura"
                    fi
                fi
            done
        else
            echo "El directorio $base no tiene permisos ejecucion"
        fi
    else
        echo "El directorio $base no existe"
    fi
else
    echo "ERROR, numero de argumentos incorrectos"
    echo "Uso: $0 [nombre] [extension]  [tamanyo de bytes] [dir1, dir2 .... dirn]"
fi