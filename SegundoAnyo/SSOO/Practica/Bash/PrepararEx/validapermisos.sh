#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripcion: Muestra una lista de permisos de los archivos pasados como argumentos

if ! [[ ${#} -lt 1 ]];then
    for file in "$@";do
        if ! [[ -z "$file" ]];then
            if ! [[ -e "$file" ]];then
                if [[ -d "$file" ]];then
                    tipo="Directorio"
                elif [[ -f "$file" ]];then
                    tipo="Fichero regular"
                elif [[ -L "$file" ]];then
                    tipo="Enlace"
                else
                    tipo="Otro"
                fi
                echo "Tipo: $tipo"
                
            else
                echo "ERROR, $file no existe"
            fi
        else
            echo "ERROR, el argumento no debe de estar vacio"
        fi
    done
else
    echo "ERROR, debe tener al menos un argumento"
fi 