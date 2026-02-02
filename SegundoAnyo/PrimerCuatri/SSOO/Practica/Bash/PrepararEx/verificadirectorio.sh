#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripcion: Verifica la accesibilidad de un directorio y muestra estadisticas basicas sobre su contenido

if [[ ${#} -ne 1 ]];then
    echo "ERROR, numero de argumentos incorrectos"
    exit
fi

dire="$1"
if [[ -z "$dire" ]];then
    echo "ERROR, argumento vacio"
    exit
fi

if [[ -e "$dire" ]];then
    if [[ -d "$dire" ]];then
        echo "Informacion sobre el directorio: $dire"
        echo "--------------------------------------"

        if [[ -r "$dire" ]];then
            echo " - Permido de lectura: Si"
        else
            echo " - Permido de lectura: NO"
        fi

        if [[ -w "$dire" ]];then
            echo " - Permido de escritura: Si"
        else
            echo " - Permido de escritura: NO"
        fi

        if [[ -x "$dire" ]];then
            echo " - Permido de ejecucion: Si"
        else
            echo " - Permido de ejecucion: NO"
        fi

        if [[ -O "$dire" ]];then
            echo " - Propietario: usuario actual (${USER})"
        else
            echo " - Propietario: distinro al usuario actual (${USER})"
        fi

        if [[ -G "$dire" ]];then
            echo " - Grupo: coincide con el grupo principal del usuario"
        else
            echo " - Grupo: no coincide con el grupo principal del usuario"
        fi
        
        ultima_mod=$(stat -c%y "$dire" 2>/dev/null)
        if [[ -n "$ultima_mod" ]];then
            echo " - Ultima modificacion: $ultima_mod"
        fi

        if [[ ! -r "$dire" || ! -x "$dire" ]];then
            echo "No se pueden obtener las estadisticas, no tenemos permisos"
            exit
        fi

        total_elementos=0
        num_subdirectorios=0
        num_archivos=0
        num_enlaces=0
        num_otros=0

        for element in "$dire"/*;do
            if [[ ! -e "$element" ]];then
                continue
            fi
            total_elementos=$((total_elementos + 1))

            if [[ -d "$element" ]];then
                num_subdirectorios=$((num_subdirectorios + 1))
            fi

            if [[ -f "$element" ]];then
                num_archivos=$((num_archivos + 1)) 
            fi

            if [[ -L "$element" ]];then
                num_enlaces=$((num_enlaces + 1))
            else
                num_otros=$((num_otros + 1))
            fi
        done

        echo "Contenido del directorio:"
        echo " - Elementos totales: $total_elementos"
        echo "   * Subdirectorios: $num_subdirectorios"
        echo "   * Archivos regulares: $num_archivos"
        echo "   * Enlaces simbolicos: $num_enlaces"
        echo "   * Otros tipos: $num_otros"

        tamanyo_dir=$(du -sh "$dire" 2>/dev/null | cur -f1)
        if [[ -n "$tamanyo_dir" ]];then
            echo " - Espacio ocupado: $tamanyo_dir"
        fi  

    else
        echo "ERROR, $dire no es un directorio"
    fi
else
    echo "ERROR, $dire no existe en el sistema"
fi