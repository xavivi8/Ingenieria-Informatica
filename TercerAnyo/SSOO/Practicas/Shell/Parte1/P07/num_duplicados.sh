#!/bin/bash
if [ $# -eq 2 ];then
	if [[ "$1" =~ ^[0-9]+$ ]];then
		if [ -f "$2" ];then
			cut -d: -f"$1" "$2" | sort | uniq -d
		else
			echo "El segundo argumento debe de ser un archivo"
			exit 1
		fi
	else
		echo "El primer argumento debe de ser un numero"
		exit 1
	fi
else
	echo "Numero de argumentos incorrecto, deben de ser 2"
	exit 1
fi
exit 0
