# Gestión de usuarios (CSV) - Python 3.11

Este proyecto crea un programa en **Python** que permite introducir usuarios por consola, mantenerlos en memoria durante la ejecución y, al salir, guardarlos en un fichero **`usuarios.csv`**.

## Requisitos

- **Windows**
- **Python 3.11**
- (Recomendado) **PyCharm**
- Un fichero principal: **`main.py`**
- El entorno virtual debe llamarse: **`.venv`**

---

## 1) Instalar Python 3.11

Descarga e instala Python 3.11 desde esta URL:

https://www.python.org/ftp/python/3.11.0/python-3.11.0-amd64.exe

> Importante: durante la instalación marca la casilla **“Add Python to PATH”**.

Para comprobar que está instalado:
```bash
python --version
```

## Entorno virtual (.venv)

### Crear el entorno virtual (solo la primera vez)
Desde la carpeta del proyecto (donde está `main.py`):

```bash
python -m venv .venv
```

## Activar el entorno virtual (entrar)

### Windows PowerShell

```bash
.\.venv\Scripts\Activate.ps1
```