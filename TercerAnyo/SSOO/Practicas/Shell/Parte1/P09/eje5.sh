#!/bin/bash
if [ $# -eq 3 ];then
	if [ -d "$1" ];then
		if [[ "$2" =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}$ ];then
			if [ "$3" =~ .?* ];then
				echo "Argumentos correctos"
			else
				echo "ERROR, el tercer argumento ${3} debe de ser una extension, .algo"
				exit 1
			fi 
		else
			echo "ERROR, el segundo argumento ${2} debe de ser una fecha año/mes/dia"
			exit 1
		fi
	else
		echo "ERROR, el primer argumento ${1} debe de ser un directorio"
		exit 1
	fi
else
	echo "ERROR, numero de argumentos invalidos, deben de ser 3"
	exit 1
fi

for cont in "$1"/*;do
	if [ -f "$cont" ] && [[ "$cont" == *"$3" ]];then
		fecha=$(ls --full-time "$cont" | cut -d' ' -f6)
		if [[ "$fecha" < "$2" ]];then
			echo "Borrando: ${cont}"
			rm "${cont}"
		fi
	fi
done

exit 0
