#!/bin/bash
if [ $# -ge 1 ];then
	for usu in "$@";do
		if grep -q "^$usu:" /etc/passwd;then
			echo "El usuario $usu se encuentra"
		else
			echo "El usuario $usu no se encuentra"
		fi
	done
else
	echo "ERROR, numeros de argumentos incorrectos, deben de ser mas de 1"
	exit 1
fi
exit 0
