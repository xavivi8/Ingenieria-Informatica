#!/bin/bash
if [ $# -ge 2 ] && [ $# -le 4 ];then
	count=0
	for argumentos in "$@";do
		count=$((count+1))
		echo "Argumento ${count} es ${argumentos}"
	done
else
	echo "ERROR, los argumentos deben de estar entre 2 y 4"
	exit 1
fi
exit 0
