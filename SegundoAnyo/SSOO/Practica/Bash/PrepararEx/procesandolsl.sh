#!/bin/bash
#Autor: Francisco Javier Martín-Lunas Escobar
#Descripción:

if ! [[ ${#} -ne 1 ]];then
    dir=${1}
    ruta="$HOME/$dir"
    if [[ -e $ruta ]];then
        if [[ -r $ruta ]];then
            if [[ -x $ruta ]];then
                ls -l $ruta > tmp 2>/dev/null
                count=0
                while read linea; do
                    primer=$(echo $linea | cut -d " " -f1)
                    if ! [[ $primer == "total" ]];then
                        name=$(echo $linea | cut -d " " -f9)
                        countX=0
                        echo "   -   Procesando linea: $linea"
                        if [[ "${primer:0:1}" == "-" ]];then
                            if [[ "${primer:1:1}" == "r"  ]];then
                                echo "$name tiene permiso de lectura para el propietario"
                            fi
                            if [[ "${primer:2:1}" == "w"  ]];then
                                echo "$name tiene permiso de escritura para el propietario"
                            fi
                            if [[ "${primer:3:1}" == "x"  ]];then
                                echo "$name tiene permiso de ejecucion para el propietario"
                                ((countX++))
                            fi
                            if [[ "${primer:4:1}" == "r"  ]];then
                                echo "$name tiene permiso de lectura para el grupo"
                            fi
                            if [[ "${primer:5:1}" == "w"  ]];then
                                echo "$name tiene permiso de escritura para el grupo"
                            fi
                            if [[ "${primer:6:1}" == "x"  ]];then
                                echo "$name tiene permiso de ejecucion para el grupo"
                                ((countX++))
                            fi
                            if [[ "${primer:7:1}" == "r"  ]];then
                                echo "$name tiene permiso de lectura para otros usuarios"
                            fi
                            if [[ "${primer:8:1}" == "w"  ]];then
                                echo "$name tiene permiso de escritura para otros usuarios"
                            fi
                            if [[ "${primer:9:1}" == "x"  ]];then
                                echo "$name tiene permiso de ejecucion para otros usuarios"
                                ((countX++))
                            fi

                            if [[ $countX -eq 3 ]];then
                                ((count++))
                            fi
                        fi
                    fi
                    
                done < tmp
                rm tmp
                echo "El numero de archivos ordinarios que tienen permisos de ejecucion activo para todos es de $count"
            else
                echo "El directorio $ruta no tien permisos de ejecucion"
            fi
        else
            echo "El directorio $ruta no tien permisos de lectura"
        fi
    else
        echo "El directorio no existe"
    fi
else
    echo "ERROR, numero de argumentos erroneo"
    echo "Uso: $0 arg1"
fi