#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripcion: Analiza un directorio y cuenta cuantos elementos hay de cada tipo

if [[ ${#} -ne 1 ]];then
    echo "ERROR, numero incorrecto de argumentos"
    exit
fi

dir="$1"

if [[ -z "$dir" ]];then
    echo "ERROR, el argumento no puede estar vacio"
fi

if [[ -e "$dir" ]];then
    if [[ -d "$dir" ]];then
        if [[ -r "$dir" ]];then
            if [[ -x "$dir" ]];then
                echo "Analizando directorio $dir"
                echo "--------------------------"

                total_elementos=0
                num_archivos=0
                num_dir=0
                num_enlaces=0
                num_otros=0

                for ruta in "$dir"/*;do
                    if [[ -e "$ruta" ]];then
                        total_elementos=$((total_elementos + 1))

                        if [[ -d "$ruta" ]];then
                            num_dir=$((num_dir + 1))
                        elif [[ -f "$ruta" ]];then
                            num_archivos=$((num_archivos + 1))
                        elif [[ -L "$ruta" ]];then
                            num_enlaces=$((num_enlaces + 1))
                        else
                            num_otros=$((num_otros + 1))
                        fi
                    else
                        echo "ERROR, no existe $ruta"
                    fi
                done

                echo "Resumen del contenido de $dir:"
                echo " - Elementos totales: $total_elementos"
                echo "   * Archivos regulares: $num_archivos"
                echo "   * Subdirectorios: $num_dir"
                echo "   * Enlaces simbolicos: $num_enlaces"
                echo "   * Otros: $num_otros"

            else
                echo "ERROR, no tenemos permiso de ejecucion en $dir"
            fi
        else
            echo "ERROR, no tenemos permiso de lectura en $dir"
        fi
    else
        echo "ERROR, $dir no es un directorio"
    fi
else
    echo "ERROR, no existe $dir"
fi