from Crypto.PublicKey import DSA
from Crypto.Signature import DSS
from Crypto.Hash import SHA256
import time

def evaluate_dsa(title, messageA):
    print(title)
    for key_size in [1024, 2048, 3072]:
        print(f"\nKey Size: {key_size} bits")
        
        # Key generation
        start = time.time()
        key = DSA.generate(key_size)
        end = time.time()
        print(f"Key Generation Time: {end - start:.6f} seconds")
        
        # Sign/Verify
        message = messageA
        h = SHA256.new(message)
        
        # Signing
        signer = DSS.new(key, 'fips-186-3')
        start = time.time()
        signature = signer.sign(h)
        end = time.time()
        print(f"Signing Time: {end - start:.6f} seconds")
        
        # Verifying
        verifier = DSS.new(key.publickey(), 'fips-186-3')
        start = time.time()
        verifier.verify(h, signature)
        end = time.time()
        print(f"Verification Time: {end - start:.6f} seconds")

evaluate_dsa("\n--- Evaluación de DSA SHORT ---",b"Hola")
evaluate_dsa("\n--- Evaluación de DSA LONG ---",b"Quillo el DSA parece que esta mas guapo")
