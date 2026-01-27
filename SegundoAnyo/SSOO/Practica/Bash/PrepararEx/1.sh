#!/bin/bash
#Autor: F
#Descripcion: Comprueba si las ordenes pasadas como argumentos existen. Si existen, muestra la ruta del ejecutable usando 'which'. Si no se pasan argumentos, muestra la sintaxis correcta"

if ! [[ ${#} -lt 1 ]];then
    for comand in "$@";do
        if ruta_comand=$(which "${comand}" 2>/dev/null);then
            
            if [[ -e "${ruta_comand}" ]];then
                if [[ -x "${ruta_comand}" ]];then
                    echo "La orden $comand esta en $ruta_comand"
                    echo "El archivo es ejecutable"
                else
                    echo "La orden $comand esta en $ruta_comand"
                    echo "El archivo no tiene permisos de ejecucion"
                fi
            else
                echo "Which indica la ruta $ruta_comand pero esta no existe"
            fi
        else
            echo "La oren ${comand} no existe"
        fi
    done
else
    echo "ERROR, al menos debe pasarse 1 argumento"
    echo "Uso: $0 orden1 [orden2 ... ordenn]"
fi