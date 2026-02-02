#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripcion: busca en un directorio archivos que compartan el mismo nombre base (ignorando su extension) y muestra sus tamaños

if [[ ${#} -ne 1 ]];then
    echo "ERROR, el numero de argumentos debe de ser 1"
    exit
fi

dir="$1"

if [[ -z "$dir" ]];then
    echo "ERROR, el argumento no puede estar vacio"
    exit
fi

if [[ -e "$dir" ]];then
    if [[ -d "$dir" ]];then
        if [[ -r "$dir" ]];then
            if [[ -x "$dir" ]];then
                echo "Analizando directorio $dir"
                echo "Buscando archivos con el mismo nombre base"
                echo "------------------------------------------"

                procesados=0
                duplicados_encontrados=0

                for ruta in "$dir"/*;do
                    if [[ ! -e "$ruta" ]];then
                        continue
                    fi
                    if [[ ! -f "$ruta" ]];then
                        continue
                    fi

                    nombre_arch=${ruta##*/}
                    base=${nombre_arch%%.*}

                    echo "$procesados" | grep -qw "$base"
                    if [[ $? -eq 0 ]];then
                        continue
                    fi

                    contador=0

                    for ruta2 in "$dir"/*;do
                        if [[ -e "$ruta2" ]];then
                            if [[ -f "$ruta2" ]];then
                                nombre2=${ruta2##*/}
                                base2=${nombre2%%.*}

                                if [[ "$base2" = "$base" ]];then
                                    contador=$((contador + 1))
                                fi
                            fi
                        fi
                    done

                    if [[ "$contador" -ge 2 ]];then
                        duplicados_encontrados=1
                        echo "Nombre base: $base"
                        echo "---------------------------"

                        for ruta2 in "$dir"/*;do
                            if [[ -e "$ruta2" ]];then
                                if [[ -f "$ruta2" ]];then
                                    nombre2=${ruta2##*/}
                                    base2=${nombre2%%.*}

                                    if [[ "$base2" = "$base" ]];then
                                        size_b=$(stat -c%s "$ruta2" 2>/dev/null)
                                        if [[ -z "$size_b" ]];then
                                            size_b=0
                                        fi
                                        echo " - $nombre2 (${size_b} bytes)"
                                    fi
                                fi
                            fi
                        done
                    fi
                    procesados="$procesados $base"
                done

                if [[ "$duplicados_encontrados" -eq 0 ]];then
                    echo "No se han encontrado archivos dupliacos"
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