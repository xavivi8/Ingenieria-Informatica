#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripción: Índice invertido de palabras

if [[ $# -ge 3 ]]; then
    indice=$1
    minlen=$2

    # comprobar que el segundo argumento es un número
    if ! [[ "$minlen" =~ ^[0-9]+$ ]]; then
        echo "ERROR, el segundo argumento debe de ser un numero"
        echo "SINTAXIS: $0 fich num [fich1 fich2 ... fichn]"
        exit 1
    fi

    # crear fichero temporal
    tmpfile=$(mktemp)
    if [[ $? -ne 0 ]]; then
        echo "ERROR, no se ha podido crear el fichero temporal"
        exit 1
    fi

    procesados=0

    # recorrer ficheros desde el tercer argumento
    for (( i=3; i<=$#; i++ )); do
        fich=${!i}

        if [[ -f "$fich" && -r "$fich" && "$fich" == *.txt ]]; then
            echo "Analizando $fich ..."
            ((procesados++))

            nombreFich=$(basename "$fich")

            while read -r linea; do
                for palabra in $linea; do
                    if (( ${#palabra} >= minlen )); then
                        echo "$palabra $nombreFich" >> "$tmpfile"
                    fi
                done
            done < "$fich"

        else
            echo "ERROR, el fichero $fich no es un fichero ordinario, no tiene permisos de lectura o no acaba en .txt"
        fi
    done

    # generar índice final y limpiar
    sort -u "$tmpfile" > "$indice"
    rm -f "$tmpfile"

    echo "Se han procesado $procesados ficheros."

else
    echo "ERROR, numero de argumentos equivocado"
    echo "SINTAXIS: $0 fich num [fich1 fich2 ... fichn]"
    exit 1
fi