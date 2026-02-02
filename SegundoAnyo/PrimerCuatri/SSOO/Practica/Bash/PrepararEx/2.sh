#!/bin/bash
#Autor: F
#Descripcion: 

if ! [[ ${#} -ne 2 ]];then
    dir_origen=$1
    dir_destino=$2

    if [[ -d "$dir_origen" && -d "$dir_destino" ]];then
        if [[ -r "$dir_origen" && -x "$dir_origen" ]];then
            if [[ -w "$dir_destino" && -x "$dir_destino" ]];then
                copiados=0

                for fich in "$dir_origen"/*;do
                    if [[ -e "$fich" ]];then
                        if [[ -f "$fich" ]];then
                            nombre_fich=$(basename fich)
                            fich_destino=$"$dir_destino/$nombre_fich"

                            if [[ ! -e "$fich_destino" ]];then
                                cp "$fich" "$fich_destino"
                                echo "Copiado: $fich"
                                copiados=$((copiados + 1))
                            elif [[ "$fich" -nt "$fich_destino" ]];then
                                cp "$fich" "$fich_destino"
                                echo "Actualizado: $nombre_fich"
                                ((copiados++))
                            else
                                acho "Saltado: $nombre_fich"
                            fi
                        fi
                    fi
                done

                if [[ "$copiados" -eq 0 ]];then
                    echo "No se han copiado ningun archivo"
                fi
            else
                echo "ERROR, $dir_destino no tiene permisos de escritura o ejecucion"
            fi
        else
            echo "ERROR, $dir_origen no tiene permisos de lectura o ejecucion"
        fi
    else
      echo "Uno de los argumentos no es un directorio, o es $dir_origen o es $dir_destino"  
    fi
else
    echo "ERROR, numero de argumentos incorrectos"
    echo "Uso: $0 dir_origen dir_destino"
fi