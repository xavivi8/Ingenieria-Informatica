#!/bin/bash
if [ $# -ne 0 ];then
	echo "ERROR, no deben pasarse argumentos"
	exit 1
fi
for archivo in "$HOME"/bin/*;do
	if [ -f "$archivo" ] && [ -x "$archivo" ];then
		if [ "$archivo" != *.sh ];then
			mv archivo  archivo".sh"
		fi
	fi
done
exit 0
