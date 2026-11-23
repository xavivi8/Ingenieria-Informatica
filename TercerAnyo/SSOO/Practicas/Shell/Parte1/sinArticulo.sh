#!/bin/bash
# Autor: Francisco Javier Martin-Lunas Escobar
# Descripción: quitar_articulos.sh fichero_frase fichero_articulos
if [ ${#} -eq 2 ]; then
    if [ -f "${1}" ] && [ -r "${1}" ] && [ -f "${2}" ] && [ -r "${2}" ]; then
        echo "Tratando de quitar los artículos del fichero ${1} usando el fichero ${2}"
    else
        echo "ERROR, Los dos argumentos deben ser ficheros legibles"
        exit 1
    fi
else
    echo "ERROR.Sintaxis: ${0} fichero_frase fichero_articulos"
    exit 1
fi

ifs_original="${IFS}"
frase_red=""
IFS=$'\n'
for linea in $(cat "${1}");do
    IFS="${ifs_original}"
    linea_red=""
    for palabra in ${linea};do
        es_articulo=no
        for art in $(cat "${2}");do
            if [ "${palabra}" = "${art}" ];then
                es_articulo=si
            fi
        done

        if [ "${es_articulo}" = no ];then
            linea_red="${linea_red} ${palabra}"
        fi
    done
    linea_red=$(echo ${linea_red})
    frase_red="${frase_red}${linea_red}"$'\n'
    IFS=$'\n'
done
IFS="${ifs_original}"

echo -n "${frase_red}" > "${1}"_red
cat "${1}"_red