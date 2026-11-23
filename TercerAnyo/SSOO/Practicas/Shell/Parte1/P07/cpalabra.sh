#!/bin/bash

if [ $# -eq 2 ];then
	if [ -f "$1" ];then
		grep -o "$2" "$1" | wc -l
	else
		echo "El primer argumento debe de ser un fichero"
	fi
else
	echo "Los argumentos deben de ser 2"
	exit 1
fi
exit 0
