#!/bin/bash
# Autor; Francisco Javier Martin-Lunas EScobar
# Descripcion: Saca los usuarios bloqueados y el numero de cuentas bloqueadas 
bloq=0
while IFS= read -r linea;do
	pass=$(echo "${linea}" | cut -d: -f2)
	if [[ ${pass} =~ ^! ]];then
		bloq=$(( bloq + 1 ))
		echo "$(echo "${linea}" | cut -d: -f1)"
	fi
done < /etc/shadow
echo "Cuentas bloqueadas: ${bloq}"
exit 1
