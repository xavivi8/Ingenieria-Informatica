#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripción:

if ! [[ ${#} -lt 3 ]];then
    name=$1
    nickName=$2
    count=0
    for (( i=3; i<=${#};i++));do
        fich=${!i}
        if [[ -e ${!i} ]];then
            if [[ -f ${!i} ]];then
                if [[ -r ${!i} ]];then
                    if [[ "${!i}" == *.txt ]];then
                        base=${fich%.txt}
                        nuevo="${base}_anonimo.txt"

                        # Crear el nuevo fichero sustituyendo name por nickName
                        sed "s/$name/$nickName/g" "$fich" > "$nuevo"

                        echo "Procesado: '$fich' -> '$nuevo'"
                        count=$((count+1))
                    else
                        echo "ERROR el archivo ${!i} no acaba en .txt"
                    fi
                else
                    echo "El fichero ${!i} no tiene permisos de lectura"
                fi
            else
                echo "El archivo ${!i} no es un archivo ordinario"
            fi
        else
            echo "ERROR, el archivo ${!i} no exste"
        fi
    done
    echo "Número de ficheros procesados: $count"
else
    echo "ERROR, se le deben pasar al menos 3 argumentos"
    echo "Uso: $0 '[nombre]' [apodo] [fich1 ... fichn]"
fi