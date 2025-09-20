from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
import time

def evaluate_rsa(title, messageA):
    print(title)
    for key_size in [1024, 2048, 3072]:
        print(f"\nKey Size: {key_size} bits")
        
        # Generación de clave
        start = time.time()
        key = RSA.generate(key_size)
        end = time.time()
        print(f"Key Generation Time: {end - start:.6f} seconds")
        
        # Preparar el cifrado y descifrado usando PKCS1_OAEP
        cipher_rsa = PKCS1_OAEP.new(key.publickey())
        decipher_rsa = PKCS1_OAEP.new(key)
        
        # Mensaje a cifrar
        message = messageA
        
        # Cifrado
        start = time.time()
        encrypted_message = cipher_rsa.encrypt(message)
        end = time.time()
        print(f"Encryption Time: {end - start:.6f} seconds")
        
        # Descifrado
        start = time.time()
        decrypted_message = decipher_rsa.decrypt(encrypted_message)
        end = time.time()
        print(f"Decryption Time: {end - start:.6f} seconds")
        
        # Verificar el descifrado
        assert decrypted_message == message, "RSA decryption failed"
        


evaluate_rsa("\n--- Evaluación de RSA SHORT ---",b"Hola")
evaluate_rsa("\n--- Evaluación de RSA LONG ---", b"Illo cifra en RSA, esto esta siendo muy largo, no puedo con esto, me quiero morir.")
