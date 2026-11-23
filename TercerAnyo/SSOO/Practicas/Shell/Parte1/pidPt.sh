#!/bin/bash
# Autor: Francisco Javier Martin-Lunas Escobar
# Descripción: Programa que muestra el Pid del proceso y los argumentos 1 y 3
if [ ${#} -ge 3 ];then
	echo "Argumento 1: ${1}"
	echo "Argumento 3: ${3}"
	echo "PID del proceso ${$}"
else
	echo "ERROR, deben de ser 3 argumentos minimo"
	exit 1
fi
exit 0
