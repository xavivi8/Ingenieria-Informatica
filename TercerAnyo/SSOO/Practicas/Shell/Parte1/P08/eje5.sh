#!/bin/bash
if [ $# -eq 2 ];then
	if [ "$1" = "$2" ];then
		echo "Ambas cadenas son iguales"
	elif [ "$1" \< "$2" ];then
		echo "La cadena ${1} esta ordenada antes que ${2}"
	else
		echo "La cadena ${1} no esta ordenada antes que ${2}"
	fi
else
	echo "ERROR, numero de argumentos incorrectos"
	exit 1
fi
exit 0
