const fs = require('fs');
const path = require('path');

const cachePath = path.join(__dirname, 'usuarios_cache.json');
let usuarios = [];

window.addEventListener('DOMContentLoaded', () => {
    const ul = document.getElementById('usuario-list');
    const form = document.getElementById('login-form');

    fetch('http://localhost:8080/app/api/usuarios')
        .then(res => {
            if (!res.ok) throw new Error("Error al conectar con el backend de usuarios");
            return res.json();
        })
        .then(data => {
            usuarios = data;
            saveToCache(usuarios);

            if (ul) {
                renderUsuarios(usuarios, ul);
            }
        })
        .catch(err => {
            console.warn("No se pudo conectar al backend de usuarios. Cargando desde caché.");
            loadFromCache(ul);
        });

    if (form) {
        form.addEventListener('submit', (e) => {
            e.preventDefault();
            validarUsuario();
        });
    }
});

function renderUsuarios(usuarios, ul) {
    ul.innerHTML = '';

    usuarios.forEach(usuario => {
        if (!usuario.administrador) {
            const li = document.createElement('li');

            li.innerHTML = `
                <div class="usuario-header">
                    <h2>${usuario.usuario}</h2>
                    <span>${usuario.administrador ? 'Administrador' : 'Cliente'}</span>
                </div>
                <div class="info">
                    <p><strong>Email:</strong> ${usuario.email}</p>
                    <p><strong>Teléfono:</strong> ${usuario.telefono}</p>
                    <p><strong>Contraseña:</strong> ${usuario.contrasena}</p>
                </div>
            `;

            if (usuario.carrito && usuario.carrito.pizzasCarrito && usuario.carrito.pizzasCarrito.length > 0) {
                const carritoDiv = document.createElement('div');
                carritoDiv.classList.add('carrito');
                carritoDiv.innerHTML = `<h3>Carrito (${usuario.carrito.pizzasCarrito.length} pizza${usuario.carrito.pizzasCarrito.length > 1 ? 's' : ''})</h3>`;

                usuario.carrito.pizzasCarrito.forEach(pizza => {
                    const pizzaDiv = document.createElement('div');
                    pizzaDiv.classList.add('pizza');

                    pizzaDiv.innerHTML = `
                        <img src="http://localhost:8080/app/${pizza.imagen}" alt="${pizza.nombre}">
                        <div class="pizza-info">
                            <h4>${pizza.nombre} (${pizza.tamanio})</h4>
                            <p><strong>Masa:</strong> ${pizza.tipoMasa}</p>
                            <p><strong>Precio:</strong> €${pizza.precio.toFixed(2)}</p>
                            <p><strong>Cantidad:</strong> ${pizza.cantidad}</p>
                            <p><strong>Ingredientes:</strong> ${pizza.ingredientes.join(', ')}</p>
                            <p>${pizza.descripcion}</p>
                        </div>
                    `;
                    carritoDiv.appendChild(pizzaDiv);
                });
                li.appendChild(carritoDiv);
            }

            ul.appendChild(li);
        }
    });
}

function saveToCache(usuarios) {
    fs.writeFileSync(cachePath, JSON.stringify(usuarios, null, 2), 'utf8');
}

function loadFromCache(ul) {
    if (fs.existsSync(cachePath)) {
        const data = fs.readFileSync(cachePath, 'utf8');
        const usuariosCache = JSON.parse(data);
        usuarios = usuariosCache;
        renderUsuarios(usuariosCache, ul);
    } else {
        ul.innerHTML = '<li>No hay datos disponibles en caché</li>';
    }
}

function validarUsuario() {
    const usuarioInput = document.getElementById('usuario').value.trim();
    const contrasenaInput = document.getElementById('contrasena').value.trim();
    const mensaje = document.getElementById('mensaje');

    const usuario = usuarios.find(u =>
        u.usuario === usuarioInput && u.contrasena === contrasenaInput
    );

    if (usuario) {
        if (usuario.administrador) {
            localStorage.setItem("adminLogueado", "true");
            window.location.href = 'admin.html';
        } else {
            localStorage.setItem("adminLogueado", "false");
            fetch("http://localhost:8080/app/", { method: 'HEAD' })
                .then(response => {
                    if (response.ok) {
                        window.location.href = "http://localhost:8080/app/";
                    } else {
                        window.location.href = "Error404.html";
                    }
                })
                .catch(error => {
                    window.location.href = "Error404.html";
                });
        }
    } else {
        mensaje.textContent = "Credenciales incorrectas.";
        mensaje.style.color = "red";
    }
}