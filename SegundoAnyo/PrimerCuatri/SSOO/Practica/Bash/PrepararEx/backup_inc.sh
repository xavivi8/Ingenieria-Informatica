#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripción:

if ! [[ $# -ne 3 ]];then
    dir1=$1
    dir2=$2
    if [[ -d "$dir1" ]];then
        if [[ -d "$dir2" ]];then
            if [[ -r "$dir1" && -x "$dir1" ]];then
                if [[ -r "$dir2" && -x "$dir2" ]];then
                    dir3=$3
                    if [[ ! -e "$dir3" ]];then
                        if mkdir "$dir3";then
                            copiados=0
                            enlazados=0
                            descartados=0
                            for fich in "$dir1"/*;do
                                echo "Procesando: $fich"
                                if [[ -f "$fich" && -r "$fich" ]];then
                                    name=$(basename "$fich")
                                    fich2="$dir2/$name"
                                    fich3="$dir3/$name"

                                    if [[ ! -e "$fich2" ]];then
                                        cp "$fich" "$fich3"
                                        ((copiados++))
                                    elif [[ "$fich" -nt "$fich2" ]];then
                                        cp "$fich" "$fich3"
                                        ((copiados++))
                                    else
                                        ln "$fich2" "$fich3"
                                        ((enlazados++))
                                    fi
                                else
                                    ((descartados++))
                                fi
                            done
                        fi
                     else
                        echo "El directorio 3, $dir3 ya existe" 
                     fi
                else
                    echo "ERROR, en $dir2 no tenemos o permisos de lectura o de ejecucion"
                fi
            else
                echo "ERROR, en $dir1 no tenemos o permisos de lectura o de ejecucion"
            fi
        else
            echo "ERROR, $dir2 no es un directorio"
        fi
    else
        echo "ERROR, $dir1 no es un directorio"
    fi
else
    echo "ERROR, el numero de argumentos es incorrecto"
    echo "SINTAXIS: $0 dir1 dir2 dir3"
fi

echo "Se han copiado $copiados ficheros en $dir3."
echo "Se han enlazado $enlazados ficheros existentes en $dir2."
echo "Se han descartado $descartados archivos o directorios."