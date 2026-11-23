#!/bin/bash
if [ $# -eq 3 ];then
	if [ -d "$1" ];then
		if [[ "$2" == .* ]];then
			if [[ "$3" =~ ^[0-9]+$ ]];then
				du -ah "$1"  | grep "\\$2\$" | sort -rh | head -n "$3"
			else
				echo "El tercer argumento tiene que ser un número"
				exit 1
			fi
		else
			echo "El segundo argumento debe de ser una extension .txt, .png, etc"
			exit 1
		fi
	else
		echo "El primer argumento debe ser un directorio"
		exit 1
	fi
else
	echo "Deben de ser 3 argumentos"
	exit 1
fi
exit 0
