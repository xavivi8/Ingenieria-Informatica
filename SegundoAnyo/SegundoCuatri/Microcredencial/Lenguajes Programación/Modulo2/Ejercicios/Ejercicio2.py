fecha = input("Introduce tu fecha de nacimiento (dd/mm/aaaa): ").strip()

partes = fecha.split("/")

if len(partes) != 3:
    print("Formato incorrecto. Usa dd/mm/aaaa.")
else:
    dia, mes, anio = partes[0].strip(), partes[1].strip(), partes[2].strip()

    # Asegurar 2 dígitos en día y mes (02, 09, etc.)
    dia = dia.zfill(2)
    mes = mes.zfill(2)

    print(f"Día: {dia} | Mes: {mes} | Año: {anio}")