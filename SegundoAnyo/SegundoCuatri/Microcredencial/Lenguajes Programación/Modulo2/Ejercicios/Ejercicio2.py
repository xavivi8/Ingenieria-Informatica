fecha = input("Pon la fecha en formato dd/mm/aaaa").strip()
dia, mes, anio = fecha.split("/")

dia = dia.zfill(2)
mes = mes.zfill(2)

print(f"Día: {dia} | Mes: {mes} | Año: {anio}")