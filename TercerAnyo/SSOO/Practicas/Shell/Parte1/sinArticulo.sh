#!/bin/bash
# Uso: quitar_articulos.sh fichero_frase fichero_articulos
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


frase_red=""
for palabra in $(cat "${1}");do
    es_articulo=no
    for art in $(cat "${2}");do
        if [ "${palabra}" = "${art}" ];then
            es_articulo=si
        fi
    done

    if [ "${es_articulo}" = no ];then
        frase_red="${frase_red} ${palabra}"
    fi
done

echo ${frase_red} > "${1}"_red
cat "${1}"_red