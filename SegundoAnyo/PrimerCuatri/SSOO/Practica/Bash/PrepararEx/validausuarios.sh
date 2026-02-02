#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripcion: Valida entre 2 a 5 nombres de usuarios recibidos cpmp argumentos. Comprueba si existen en el sistema y, en tal caso, muestra su UID.

if [[ ${#} -lt 2 || ${#} -gt 5 ]];then
    echo "ERROR, numero de argumentos incorrectos, deben de ser de 2 a 5 argumentos"
    exit
fi

base_usu="/etc/passwd"

if [[ -e "$base_usu" ]];then
    if [[ -f "$base_usu" ]];then
        if [[ -r "$base_usu" ]];then
            echo "Comprobando usuarios en el sistema..."
            echo "-------------------------------------"

            for usu in "$@";do
                linea_usu=$(grep "^${usu}:" "$base_usu")

                if [[ -z "$linea_usu" ]];then
                    echo "Usuario: $usu no existe"
                else
                    uid=$(echo "$linea_usu" | cut -d: -f3)
                    home_dir=$(echo "$linea_usu" | cut -d: -f6)
                    shell_login=$(echo "$linea_usu" | cut -d: -f7)

                    echo "Usuario: $usu existe"
                    echo "   UID: $uid"
                    echo "   Home: $home_dir"
                    echo "   Shell: $shell_login"
                fi
            done
        else
            echo "ERROR, no se puede leer '$base_usu'"
        fi
    else
        echo "ERROR, '$base_usu' no es un archivo regular"
    fi
else
    echo "ERROR, el fichero de usuarios '$base_usu' no existe"
fi