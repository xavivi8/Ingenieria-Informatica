#!/bin/bash

if [ $# -eq 2 ];then
	if [ -f "$1" ];then
		sort "$1" | uniq > "$2"
	else
		echo "Ambos argumentos deben de ser ficheros"
		exit 1
	fi
else
	echo "El numero de argumentos debe de ser 2"
	exit 1
fi
exit 0
