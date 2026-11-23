#!/bin/bash
if [ $# -eq 2 ];then
	if [ -d "$1" ];then
		if [[ "$2" =~ ^[0-9]+$ ]];then
			ls -l "$1" | tail -n +2 | sort -k2,2 -nr | head -n "$2"
		else
			echo "El segundo argumento debe de ser un numero"
			exit 1
		fi
	else
		echo "El primer argumento debe de ser un directorio"
		exit 1
	fi
else
	echo "Deben de ser 2 argumentos"
	exit 1
fi
exit 0
