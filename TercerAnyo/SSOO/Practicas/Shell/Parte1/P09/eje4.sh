S#!/bin/bash
if [ $# -eq 2 ];then
	if [ -d "$1" ] && [ -d "$2" ];then
		echo "El directorio ${1} y ${2} son accesibles"
	else
		echo "Alguno de los dos argumentos o no son directorios o no son accesibles"
		exit 1
	fi
else
	echo "ERROR, los argumentos deben de ser 2"
	exit 1
fi

for arcD1 in "$1"/*;do
	if [ -f "$arcD1" ];then
		nombre=$(basename "$arcD1")
		if [ ! -e "$2/$nombre" ] || [ "$arcD1" -nt "$2/$nombre"];then
			cp -p "$arcD1" "$2/"
			echo "Copiado: $arcD1"
		else
			echo "No copiando $arcD1"
		fi
	fi
done

exit 0
