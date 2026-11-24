#!/bin/bash
# Autor: Francisco Javier Martin-Lunas Escobar
# Descripcion: Comprobar que el UID que pasen existe y comprobar si coincide con su GID
if [ ${#} -eq 1 ];then
	if [[ ${1} =~ ^[0-9]+$ ]];then
		echo "${1} tiene estructura de UID"
	else
		echo "ERROR, ${1} no es un UID"
		exit 1
	fi
else
	echo "ERROR, hay ${#} argumento/s y debe de ser un solo argumento"
	exit 1
fi

while IFS= read -r linea;do
	uid=$(echo "${linea}" | cut -d: -f3)
	if [[ ${1} -eq ${uid} ]];then
		echo "Existe un usuario cuyo UID sea ${uid}"
		gid=$(echo "${linea}" | cut -d: -f4)
		if [[ ${uid} -eq ${gid} ]];then
			echo "Tienen el mismo UID (${uid}) y el mismo GID  (${gid})"
		else
			echo "No tienen el midmo UID (${uid}) y el mismo GID (${gid})"
		fi
		exit 0
	fi
done < /etc/passwd
echo "No existe ningun usuario con UID ${1}"
exit 0
