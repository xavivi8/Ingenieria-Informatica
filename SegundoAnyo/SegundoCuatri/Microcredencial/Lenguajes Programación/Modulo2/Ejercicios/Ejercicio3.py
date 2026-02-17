BASE = 2400
EPS = 1e-9

puntuacion = float(input("Introduce tu puntuación (0.0, 0.4, 0.6 o más): "))

if abs(puntuacion - 0.0) < EPS:
    nivel = "Inaceptable"
    bonificacion = 0.0
elif abs(puntuacion - 0.4) < EPS:
    nivel = "Aceptable"
    bonificacion = BASE * puntuacion
elif puntuacion >= 0.6:
    nivel = "Meritorio"
    bonificacion = BASE * puntuacion
else:
    print("Error: Puntuación inválida. Los valores permitidos son 0.0, 0.4, 0.6 o superiores.")
    raise SystemExit

print(f"Tu nivel de rendimiento es: {nivel}. Te corresponde una bonificación de: {bonificacion:.2f}€")
