from Crypto.PublicKey import ECC
from Crypto.Signature import DSS
from Crypto.Hash import SHA256
import time

def evaluate_ecc(title, messageA):
    print(title)
    for curve_name in ["P-256", "P-384", "P-521"]:
        print(f"\nCurve: {curve_name}")
        
        # Key generation
        start = time.time()
        key = ECC.generate(curve=curve_name)
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
        verifier = DSS.new(key.public_key(), 'fips-186-3')
        start = time.time()
        verifier.verify(h, signature)
        end = time.time()
        print(f"Verification Time: {end - start:.6f} seconds")

evaluate_ecc("\n--- Evaluación de ECC SHORT ---",b"Hola")
evaluate_ecc("\n--- Evaluación de ECC LONG ---",b"Quillo el ECC va mas rapido que flash")
