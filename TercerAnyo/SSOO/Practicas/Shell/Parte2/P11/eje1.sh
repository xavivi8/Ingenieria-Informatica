#!/bin/bash
# Autor: Francisco Javier Martin-Lunas Escobar
# Descripcion: Escribir por pantalla los usuarios que no son del sistema 

if [ ${#} -eq 0 ];then
	while IFS= read -r linea;do
		uid=$(echo ${linea} | cut -d: -f3)
		if [[ ${uid} -ge 1000 ]];then
			dir_usu=$(echo ${linea} | cut -d: -f6 | cut -d/ -f2)
			echo "${linea}"
			echo "${dir_usu}"
			if [[ ${dir_usu} -eq "home" ]];then
				echo "Si"
			fi
		fi
	done < /etc/passwd
else
	echo "ERROR, los argumentos deben de ser 0" >&2
	exit 1
fi
exit 0
