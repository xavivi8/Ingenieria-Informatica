#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripcion: Verificar la existencia, permisos y tamaño de un archivo pasado como argumento

if [[ ${#} -ne 1 ]];then
    echo "ERROR, numero de argumentos incorrectos"
    exit
fi

nombre_archivo="${1}"

if [[ -z "${nombre_archivo}" ]];then
    echo "ERROR, cadena vacia"
    exit
fi

if [[ -e "${nombre_archivo}" ]];then
    if [[ ! -d ${nombre_archivo} ]];then
        if [[ -f "${nombre_archivo}" ]];then
            echo "Informacion del archivo ${nombre_archivo}"
            echo "-----------------------------------------"

            if [[ -s "${nombre_archivo}" ]];then
                echo " - Contenido: el archivo NO esta vacio"
            else
                echo " - Contenido: el archivo está vacio"
            fi

            if [[ -r "${nombre_archivo}" ]];then
                echo " - Permiso de lectura: SI"
            else
                echo " - Permiso de lectura: NO"
            fi

            if [[ -w "${nombre_archivo}" ]];then
                echo " - Permiso de escritura: SI"
            else
                echo " - Permiso de escritura: NO"
            fi

            if [[ -x "${nombre_archivo}" ]];then
                echo " - Permiso de ejecucion: SI"
            else
                echo " - Permiso de ejecucion: NO"
            fi

            if [[ -O "${nombre_archivo}" ]];then
                echo " - Propietario: el usuario actual (${USER})"
            else
                echo " - Propietario: otro usuario"
            fi

            if [[ -G "${nombre_archivo}" ]];then
                echo " - Grupo: coincide con el grupo del usuario actual"
            else
                echo " - Grupo: NO coincide con el grupo del usuario actual"
            fi

            tamanyo=$(stat -c%s "${nombre_archivo}" 2>/dev/null)
            if [[ $? -eq 0 && -n "${tamanyo}" ]];then
                echo " - tamanyo: ${tamanyo} bytes"
            else
                echo " - Tamanyo: no se pudo obtener"
            fi

            tamanyo_legible=$(du -h "${nombre_archivo}" 2>/dev/null | cut -f1)
            if [[ $? -eq 0 && -n "${tamanyo_legible}" ]];then
                echo " - Tamanyo legible: ${tamanyo_legible}"
            fi
        else
            echo "ERROR, '${nombre_archivo}' no es un archivo regular"
        fi
    else
        echo "ERROR, el archivo '${nombre_archivo}' es un directorio y no un archivo regular"
    fi
else
    echo "ERROR, el archivo '${nombre_archivo}' no existe en el sistema"
fi