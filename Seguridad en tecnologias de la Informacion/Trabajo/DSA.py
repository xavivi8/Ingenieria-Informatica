from Crypto.PublicKey import DSA # Proporciona funcionalidad para generar claves DSA
from Crypto.Signature import DSS #Gestiona las firmas y verificaciones según el estándar FIPS-186-3
from Crypto.Hash import SHA256 # Algoritmo de has utilizado para crear un resumen del mensaje
import time #Se usa para medir los tiempos de ejecucuón de distintas operaciones

def evaluate_dsa(title, messageA):
    print(title)
    '''
    El código evalúa el rendimiento para las claves 1024, 2048 y 3072 bits, donde:
        -Claves más grandes proporcionan mayor seguridad
        -Claves más pequeñas son más rápidas en términos de generación t procesamiento
    '''
    for key_size in [1024, 2048, 3072]:
        print(f"\nKey Size: {key_size} bits")
        
        # Generación de clave
        start = time.time()
        key = DSA.generate(key_size)
        end = time.time()
        print(f"Key Generation Time: {end - start:.6f} seconds")
        
        # Firmar/Verificar
        message = messageA
        h = SHA256.new(message)
        
        # Firmar el hash del mensaje
        signer = DSS.new(key, 'fips-186-3')
        start = time.time()
        signature = signer.sign(h)
        end = time.time()
        print(f"Signing Time: {end - start:.6f} seconds")
        
        # Verificar la firma
        verifier = DSS.new(key.publickey(), 'fips-186-3')
        start = time.time()
        verifier.verify(h, signature)
        end = time.time()
        print(f"Verification Time: {end - start:.6f} seconds")

evaluate_dsa("\n--- Evaluación de DSA SHORT ---",b"Hola")
evaluate_dsa("\n--- Evaluación de DSA LONG ---",b"Quillo el DSA parece que esta mas guapo")
