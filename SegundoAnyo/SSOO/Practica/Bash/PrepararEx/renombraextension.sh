#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripcion: Añade una extension concreta a todos los archivos regulares de un directorio, siempre que no tengan ya una

if [[ ${#} -ne 2 ]];then
    echo "ERROR, deben pasarse 2 argumentos"
    exit
fi

dire="$1"
ext="$2"

if [[ ! -z "$dire" && ! -z "$ext" ]];then
    primer_caracter="${ext:0:1}"

    if [[ "$primer_caracter" = "." ]];then
        ext="${ext#.}"
    fi
    
    if [[ -e "$dire" ]];then
        if [[ -d "$dire" ]];then
            if [[ -r "$dire" ]];then
                if [[ -x "$dire" ]];then
                    echo "Directorio a procesar $dire"
                    echo "Extension deseada     : .$ext"

                    total_archivos=0
                    archivos_ya_ok=0
                    archivos_candidatos=0
                    archivos_renombrados=0

                    for ruta in "$dire"/*;do
                        if [[ ! -e "$ruta" || ! -f $ruta ]];then
                            continue
                        fi

                        total_archivos=$((total_archivos + 1))
                        nombre_archivo=$(basename "$ruta")

                        if [[ "$nombre_archivo" == *".${ext}" ]];then
                            echo "El archivo $nombre_archivo ta tiene la extension.$ext"
                            archivos_ya_ok=$((archivos_ya_ok + 1))
                            continue
                        fi

                        archivos_candidatos=$((archivos_candidatos + 1))
                        nuevo_nombre="${nombre_archivo}.${ext}"
                        destino="$dire/$nuevo_nombre"

                        if [[ ! -e "$destino" ]];then
                            echo "Renombrar $nombre_archivo -> $nuevo_nombre? (S/N)"
                            read respuesta

                            if [[ "$respuesta" = "s" || "$respuesta" = "S" ]];then
                                mv -- "$ruta" "$destino"

                                if [[ $? -eq 0 ]];then
                                    echo "  Renombrado correctamente"
                                    archivos_renombrados=$((archivos_renombrados + 1))
                                else
                                    echo "  Error al renombrar $nombre_archivo"
                                fi
                            else
                                echo "  Se ga omitido $nombre_archivo"
                            fi
                        fi
                    done

                    echo "Resumen:"
                    echo " - Archivos regulares encontrados: $total_archivos"
                    echo " - Archivos ya existen con la extension .$ext: $archivos_ya_ok"
                    echo " - Archivos candidatos a renombrar: $archivos_candidatos"
                    echo " - Archivos finalmente renombrados: $archivos_renombrados"
                else
                    echo "ERROR; no se puede acceder a $dire"
                fi
            else
                echo "ERROR, no se puede leer el contenido de $dire"
            fi
        else
            echo "ERROR, $dire no es un directorio"
        fi
    else
        echo "ERROR, el directorio $dire no existe"
    fi
else
    echo "ERROR, los argumentos no pueden ser cadenas vacias"
fi