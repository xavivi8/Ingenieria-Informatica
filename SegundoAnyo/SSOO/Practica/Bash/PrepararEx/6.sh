#!/bin/bash
#Autor: F
#Descripcion: 

if [[ ${#} -lt 1 ]];then
    echo "ERROR"
    exit
fi

for user in "$@";do
    echo "=========================="
    echo "Procesando usuario:$user"

    dirbase=$(dirname "$HOME")"$user"
    if [[ ! -d "$dirbase" ]];then
        echo "ERROR, $dirbase no es un directorio"
        continue
    fi

    if [[ ! -r "$dirbase" || ! -x "$dirbase" ]];then
        echo "ERROR"
        continue
    fi

    dirbin="$dirbase/bin"

    if [[ ! -d "$dirbin" ]];then
        if [[ ! -w "$dirbin" ]];then
            echo "No se puede crear $dirbin"
            continue
        fi
    else
        echo "El directorio bin ya existe $dirbin"
        if [[ ! -w "$dirbin" ]];then
            echo "Pero no se puede escribir en $dirbin"
            continue
        fi
    fi

    actual=$(pwd)
    cd "$dirbin" ||  {
        echo "ERROR, no se puede entrar en $dirbin"
        continue
    }

    exes=$(ls -F | grep "*" | sed 's/*//G')
    if [[ -z "$exes" ]];then
        echo "No hay ficheros ejecutables en $dirbin"
        continue
    fi

    echo "Ejecutables encontrados $exes"

    for fichero in $exes;do
        if [[ -f "$fichero" && -x "$fichero" ]];then
            mv "$fichero" "$dirbin/"
            echo "Movido $fichero -> $dirbin/"
        fi
    done
    cd "$actual"
done