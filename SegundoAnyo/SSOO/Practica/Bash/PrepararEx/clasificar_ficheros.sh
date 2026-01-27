#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripción: 

if ! [[ ${#} -ne 2 ]];then
    dir_origen="$1"
    dir_destino="$2"
    if [[ -d "$dir_origen" ]];then
        if [[ -r "$dir_origen" && -x "$dir_origen" ]];then
            if ! [[ -e "$dir_destino" ]];then
                mkdir "$dir_destino"
            fi

            if [[ -w "$dir_destino" && -x "$dir_destino" ]];then
                clasificado=0
                descartado=0
                for fich in "$dir_origen"/*;do
                    if [[ -e "$fich" ]];then
                        if [[ -f "$fich" ]];then
                            if [[ -r "$fich" ]];then
                                name_fich=$(basename "$fich")
                                if [[ "$name_fich" == *.* ]]; then
                                    exte_fich="${name_fich##*.}"
                                    if [[ -z "$exte_fich" || "$exte_fich" == "$name_fich" ]]; then
                                        exte_fich="sin_extension"
                                    fi
                                else
                                    exte_fich="sin_extension"
                                fi

                                subdir="$dir_destino/$exte_fich"

                                if [[ ! -d "$subdir" ]]; then
                                    if ! mkdir -p "$subdir"; then
                                        echo "ERROR al crear el subdirectorio $subdir"
                                        ((descartado++))
                                    fi
                                fi

                                if [[ -w "$subdir" && -x "$subdir" ]];then
                                    echo "Clasificando: $name_fich -> $subdir/$name_fich"

                                    if mv "$fich" "$subdir/";then
                                        ((clasificado++))
                                    else
                                        echo "ERROR al mover el archivo"
                                        ((descartado++))
                                    fi
                                else
                                    echo "ERROR, no hay acceso al subdirectorio $subdir"
                                    ((descartado++))
                                fi

                            else
                                ((descartado++))
                            fi
                        else
                            ((descartado++))
                        fi
                    fi
                done
                echo "Se han clasificado $clasificado ficheros en total."
                echo "Se han descartado $descartado archivos o directorios."
            else
                echo "ERROR, no hay permisos de acceso a $dir_destino"
            fi
        else
            echo "ERROR, no hay permisos de acceso a $dir_origen"
        fi
    else
        echo "ERROR, $dir_origen no es un directorio"
    fi
else
    echo "ERROR, número de argumentos incorrecto"
    echo "SINTAXIS: $0 dir_origen dir_destino"
fi