# Instalaciones
pip install pycryptodome

## Análisis del Código de DSA
**Importación de librerías**
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
**Mostrar las claves publicas y privadas**
```py
private_key = key.export_key()
public_key = key.publickey().export_key()
print(f"\nPrivate Key: \n{private_key.decode()}")
print(f"\nPublic Key: \n{public_key.decode()}")
```
- `key.export_key()`: Este método exporta la clave en formato PEM (un formato textual que contiene la clave codificada en base64), que es un formato estándar ampliamente utilizado.
- `key.publickey().export_key()`: Este método exporta la clave pública en formato PEM.
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
- `key.publickey()`: Obtiene la clave pública asociada a la clave privada generada previamente.
- `verifier.verify(h, signature)`: Verifica si la firma es válida comparando el hash firmado y la clave pública.
- **Tiempo de ejecución**: Mide el tiempo necesario para verificar la firma.
#
**LLamadas a la función**
```py
evaluate_dsa("\n--- Evaluación de DSA SHORT ---", b"Hola")
evaluate_dsa("\n--- Evaluación de DSA LONG ---", b"Quillo el DSA parece que esta mas guapo")
```
- Evalúa el rendimiento con dos mensajes:
- Permite comparar cómo el tamaño del mensaje afecta los tiempos de firmado y verificación.