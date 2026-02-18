import csv
import re


CSV_FILENAME = "usuarios.csv"
EMAIL_DOMAIN = "@uja.es"


class Usuario:
    def __init__(self, user_id: int, nombre: str, apellidos: str, email: str, dni: str, telefono: str):
        self.id = user_id
        self.nombre = nombre
        self.apellidos = apellidos
        self.email = email
        self.dni = dni
        self.telefono = telefono  # puede ser "" si no se introduce

    def to_dict(self) -> dict:
        return {
            "id": self.id,
            "nombre": self.nombre,
            "apellidos": self.apellidos,
            "email": self.email,
            "dni": self.dni,
            "telefono": self.telefono
        }


def normalizar_texto(s: str) -> str:
    return s.strip()


def validar_no_vacio(valor: str) -> bool:
    return len(valor.strip()) > 0


def validar_email(email: str) -> bool:
    email = email.strip().lower()
    # Formato mínimo: algo@uja.es (sin espacios)
    if " " in email:
        return False
    if not email.endswith(EMAIL_DOMAIN):
        return False
    parte_local = email[:-len(EMAIL_DOMAIN)]
    return len(parte_local) > 0


def validar_dni(dni: str) -> bool:
    dni = dni.strip().upper()
    # 8 dígitos + 1 letra
    return re.fullmatch(r"\d{8}[A-Z]", dni) is not None


def validar_telefono(telefono: str) -> bool:
    telefono = telefono.strip()
    # Opcional: si vacío, OK. Si no, 9 dígitos exactos
    if telefono == "":
        return True
    return telefono.isdigit() and len(telefono) == 9


def pedir_campo_obligatorio(mensaje: str, funcion_validacion, funcion_normalizacion=None) -> str:
    while True:
        valor = input(mensaje)
        if funcion_normalizacion:
            valor = funcion_normalizacion(valor)
        if funcion_validacion(valor):
            return valor
        print("❌ Valor inválido. Inténtalo de nuevo.")


def pedir_telefono_opcional(mensaje: str) -> str:
    while True:
        valor = input(mensaje).strip()
        if validar_telefono(valor):
            return valor  # puede ser ""
        print("❌ Teléfono inválido. Debe tener exactamente 9 dígitos o dejarse vacío.")


def crear_usuario(siguiente_id: int) -> Usuario:
    nombre = pedir_campo_obligatorio(
        "Nombre (obligatorio): ",
        validar_no_vacio,
        normalizar_texto
    )

    apellidos = pedir_campo_obligatorio(
        "Apellidos (obligatorio): ",
        validar_no_vacio,
        normalizar_texto
    )

    email = pedir_campo_obligatorio(
        f"Email (obligatorio, formato usuario{EMAIL_DOMAIN}): ",
        validar_email,
        lambda s: s.strip().lower()  # normalización: minúsculas
    )

    dni = pedir_campo_obligatorio(
        "DNI (obligatorio, 8 números + 1 letra, ej 12345678Z): ",
        validar_dni,
        lambda s: s.strip().upper()  # normalización: mayúsculas
    )

    telefono = pedir_telefono_opcional("Teléfono (opcional, 9 dígitos o vacío): ")

    return Usuario(
        user_id=siguiente_id,
        nombre=nombre.strip(),
        apellidos=apellidos.strip(),
        email=email.strip().lower(),
        dni=dni.strip().upper(),
        telefono=telefono
    )


def mostrar_usuarios(usuarios: list[Usuario]) -> None:
    if not usuarios:
        print("No hay usuarios creados todavía.")
        return

    print("\nUsuarios en memoria:")
    print("-" * 80)
    for u in usuarios:
        tel = u.telefono if u.telefono != "" else "(vacío)"
        print(f"ID: {u.id} | {u.nombre} {u.apellidos} | {u.email} | {u.dni} | Tel: {tel}")
    print("-" * 80)


def guardar_csv(usuarios: list[Usuario], filename: str) -> None:
    encabezados = ["id", "nombre", "apellidos", "email", "dni", "telefono"]
    with open(filename, mode="w", newline="", encoding="utf-8") as f:
        writer = csv.DictWriter(f, fieldnames=encabezados)
        writer.writeheader()
        writer.writerows([u.to_dict() for u in usuarios])


def menu() -> str:
    print("\n=== MENÚ ===")
    print("1) Crear usuario")
    print("2) Leer usuarios")
    print("0) Salir (guarda en usuarios.csv)")
    return input("Elige una opción: ").strip()


def main():
    usuarios: list[Usuario] = []
    next_id = 1

    while True:
        opcion = menu()

        if opcion == "1":
            usuario = crear_usuario(next_id)
            usuarios.append(usuario)
            next_id += 1
            print("✅ Usuario creado y guardado en memoria.")

        elif opcion == "2":
            mostrar_usuarios(usuarios)

        elif opcion == "0":
            guardar_csv(usuarios, CSV_FILENAME)
            print(f"✅ Programa finalizado. CSV generado: {CSV_FILENAME}")
            break

        else:
            print("❌ Opción inválida. Elige 1, 2 o 0.")


if __name__ == "__main__":
    main()