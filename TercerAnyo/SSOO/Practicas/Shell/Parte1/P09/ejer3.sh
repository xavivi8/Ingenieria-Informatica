#!/bin/bash
if [ $# -ge 1 ];then
	for dir in "$@";do
		if [ -d "$dir" ];then
			echo "Contenido del directorio ${dir}"
			ls -l $dir
		else
			echo "El argumento ${dir} o no es un directorio o no es accesible desde esta posicion"
		fi
	done
else
	echo "No ha pasado ningun directorio"
fi
exit 0
