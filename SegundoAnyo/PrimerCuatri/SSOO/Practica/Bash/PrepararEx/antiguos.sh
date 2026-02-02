#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripcion: Muestra los N archivos mas antiguos de un directorio y permite eliminarlos de forma interactiva

if [[ ${#} -ne 2 ]];then
    echo "ERROR, numero incorrecto de argumentos"
    exit
fi

dir="$1"
n="$2"

if [[ -z "$dir" || -z "$n" ]];then 
    echo "ERROR, no pueden pasarse argumentos vacios"
    exit
fi

if [[ -e "$dir" ]];then
    if [[ -d "$dir" ]];then
        if [[ -r "$dir" ]];then
            if [[ -x "$dir" ]];then
                if [[ "$n" =~ ^[1-9][0-9]*$ ]];then
                    echo "Analizando directorio $dir"
                    echo "Buscando los $n archivos mas antiguos"
                    echo "-------------------------------------"

                    cd "$dir" || {
                        echo "ERROR, no se pudo acceder a $dir"
                        exit
                    }

                    count=0
                    procesados=0

                    for nombre in $(ls -1tr 2>/dev/null);do
                        if [[ -f "$nombre" ]];then
                            procesados=$((procesados + 1))
                            count=$((count + 1))

                            echo "[$count] Archivo antiguo encontrado"
                            ls -l --full-time "$nombre"

                            echo "¿Desea eliminar este archivo? (S/N)"
                            read respuesta

                            if [[ "$respuesta" = "s" || "$respuesta" = "S" ]];then
                                rm -- "$nombre"
                                if [[ $? -eq 0 ]];then
                                    echo "  Archivo eliminado correctamente"
                                else
                                    echo "  ERROR al eliminar $nombre"
                                fi
                            else
                                echo "  Archivo conservado"
                            fi

                            if [[ "$count" -eq "$n" ]];then
                                break
                            fi
                        fi
                    done

                    if [[ "$count" -eq 0 ]];then
                        echo "No se han encontrado archivos regulares en el directorio"
                    else
                        if [[ "$count" -eq "$n" ]];then
                            echo "Solo se han encontrado $count archivos"
                        else
                            echo "Se ha nprocesado los $n archivos mas antiguos"
                        fi
                    fi

                else
                    echo "ERROR, debe de ser un numero entero positvo"
                fi
            else
                echo "ERROR, no tenemos permisos de ejecucion en $dir"
            fi
        else
            echo "ERROR, no tenemos permisos de lectura en $dir"
        fi
    else
        echo "ERROR, $dir no es un directorio"
    fi
else
    echo "ERROR, no existe $dir"
fi