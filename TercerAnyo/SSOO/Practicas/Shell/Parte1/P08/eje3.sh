#!/bin/bash
if [ $# -eq 1 ];then
	if [ ! -d "$1" ];then
		mkdir "$1"
	fi
	chmod 700 "$1"
else
	echo "ERROR, debe de ser un solo argumento"
	exit 1
fi
exit 0
