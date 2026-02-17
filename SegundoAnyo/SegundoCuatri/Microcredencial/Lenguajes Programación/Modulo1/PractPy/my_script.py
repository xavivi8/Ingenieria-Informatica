import pandas as pd
import sys
print(f"--- Versión de Pandas: {pd.__version__} ---")
print(f"--- Ejecutando desde: {sys.prefix} ---\n")
df1 = pd.DataFrame({'A': [1, 2]})
df2 = pd.DataFrame({'A': [3]})
try:
# Funciona en Pandas 1.x / Falla en Pandas 2.x
    resultado = df1.append(df2)
    print("¡Éxito! El método .append() funcionó.")
except AttributeError:
    print("¡ERROR! El método .append() fue eliminado en esta versión.")
    print("Debes usar 'pd.concat([df1, df2])' ahora.")