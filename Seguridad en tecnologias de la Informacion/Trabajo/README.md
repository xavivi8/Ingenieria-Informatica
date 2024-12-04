# Instalaciones
pip install pycryptodome

## Análisis del Código de DSA
### Importación de librerías
``` py
from Crypto.PublicKey import DSA
from Crypto.Signature import DSS
from Crypto.Hash import SHA256
import time
```
- `DSA`: Proporciona funcionalidad prar generar claves DSA.
- `DSS`: Gestiona las firmas y verificaciones según el estándar FIPS-186-3
- `SHA256`: Algoritmo de hash utlizado para crear un resumen del mensaje.
- `time`: Se usa para medir los tiempos de ejecución de distintas operaciones.
#
**Difinición de la función** `evaluate_dsa`<br>
La función evalúa el rendimiento del algoritmo DSA pra diferentes tamaños de clave y dos mensajes de entrada.<br><br>
**Entrada de la función:**<br>
- `title`: Título que indica el contexto de la evaluación
- `messageA`: Mensaje (en formato `bytes`) que será firmado y verificado.
#
**Ciclo por tamaños de clave:**
```py
for key_size in [1024, 2048, 3072]:
```
El código evalúa el rendimiento para claves de **1024**, **2048** y **3072** bits, donde:
- Claves más grandes proporcionan mayor seguridad.
- Claves más pequeñas son más rápidas en términos de generación y procesamiento.
#
**Generación de claves:**
```py
start = time.time()
key = DSA.generate(key_size)
end = time.time()
print(f"Key Generation Time: {end - start:.6f} seconds")
```
- Se genera un par de claves (privada y pública) para el tamaño especificado.
- **Tiempo de ejecución**: Se mide cuánto tarda en generar el par de claves.
#
**Creación del hash del mensaje:**
```py
h = SHA256.new(message)
```
- Convierte el mensaje de entrada (`messageA`) en un hash SHA-256. Este hash es lo que será firmado, asegurando integridad y compatibilidad con el estándar DSA.
#
**Firma del hash:**
```py
signer = DSS.new(key, 'fips-186-3')
start = time.time()
signature = signer.sign(h)
end = time.time()
print(f"Signing Time: {end - start:.6f} seconds")
```
- `DSS.new(key, 'fips-186-3')`: Crea un objeto para firmar usando la clave privada.
- `signer.sign(h)`: Firma el hash con la clave privada generando una firma digital.
- **Tiempo de ejecución**: Mide el tiempo requerido para firmar.
#
**Verificación de la firma:**
```py
verifier = DSS.new(key.publickey(), 'fips-186-3')
start = time.time()
verifier.verify(h, signature)
end = time.time()
print(f"Verification Time: {end - start:.6f} seconds")
```