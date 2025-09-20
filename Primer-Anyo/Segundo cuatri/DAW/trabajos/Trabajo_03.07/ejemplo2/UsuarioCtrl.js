const el = selector => document.querySelector(selector);

class UsuariosCtrl {
    constructor() {
        this.srvUrl = "api/usuarios";
        this.usuarios = [];
    }

    init() {
        const formRegistro = el('#fAlta');
        console.log('Formulario encontrado:', formRegistro);
        if (formRegistro) {
            formRegistro.addEventListener('submit', e => this.alta(e));
            console.log('Formulario encontrado, manejador de evento asignado');
        } else {
            console.error('Formulario no encontrado');
        }

        this.cargaUsuarios();

        console.log('Controlador de usuarios iniciado');
    }

    cargaUsuarios() {
        fetch(this.srvUrl)
            .then(response => response.json())
            .then(usuarios => {
                this.usuarios = usuarios;
                this.visualizaUsuarios();
            })
            .catch(() => {
                el('#errores').innerHTML = "Error al obtener los usuarios";
                console.error("Error al obtener los usuarios");
            });
    }

    visualizaUsuarios() {
        let ul = el('#listaUsuarios');
        ul.innerHTML = '';

        this.usuarios.forEach(usuario => {
            let li = document.createElement('li');
            li.className = 'list-group-item d-flex justify-content-between align-items-center';

            const nombreSpan = document.createElement('span');
            nombreSpan.innerHTML = `<a href="#" data-id="${usuario.id}"><b>${usuario.nombre}</b></a> (${usuario.usuario})`;
            nombreSpan.querySelector('a').addEventListener('click', e => {
                e.preventDefault();
                this.mostrarDetalle(usuario.id);
            });

            li.appendChild(nombreSpan);

            if (usuario.rol !== 'ADMINISTRADOR') {
                const borrarLink = document.createElement('a');
                borrarLink.href = '#';
                borrarLink.textContent = 'Borrar';
                borrarLink.addEventListener('click', e => {
                    e.preventDefault();
                    this.borrado(usuario.id, e);
                });
                li.appendChild(borrarLink);
            }

            ul.appendChild(li);
        });
    }

    async alta(event) {
        event.preventDefault();

        const erroresDiv = el('#errores');
        erroresDiv.innerHTML = '';

        const datos = {
            nombre: el('input[name="nombre"]').value,
            usuario: el('input[name="usuario"]').value,
            email: el('input[name="email"]').value,
            contrasena: el('input[name="contrasena"]').value,
            dni: el('input[name="dni"]').value,
            numeroDeTarjeta: el('input[name="numeroDeTarjeta"]').value,
            telefono: el('input[name="telefono"]').value,
            direccion: el('textarea[name="direccion"]').value,
            fechaNacimiento: el('input[name="fechaNacimiento"]').value
        };

        try {
            const response = await fetch(this.srvUrl, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(datos)
            });

            if (response.ok) {
                erroresDiv.innerHTML = '<p class="text-success">Usuario registrado correctamente.</p>';
                el('#fAlta').reset();
                this.cargaUsuarios();
            } else if (response.status === 400) {
                const errores = await response.json();

                document.querySelectorAll('[data-error-for]').forEach(el => el.innerText = '');
                erroresDiv.innerHTML = '';

                if (Array.isArray(errores)) {
                    errores.forEach(error => {
                        const campoError = document.querySelector(`[data-error-for="${error.name}"]`);
                        if (campoError) {
                            campoError.innerText = error.message;
                        } else {
                            erroresDiv.innerHTML += `<p class="text-danger">${error.name}: ${error.message}</p>`;
                        }
                    });
                } else {
                    erroresDiv.innerHTML = '<p class="text-danger">Error de validación inesperado</p>';
                }

            } else {
                erroresDiv.innerHTML = `<p class="text-danger">Error inesperado (${response.status})</p>`;
            }
        } catch (err) {
            erroresDiv.innerHTML = `<p class="text-danger">Error de conexión: ${err.message}</p>`;
        }
    }

    async borrado(id, event) {
        event.preventDefault();

        const erroresDiv = el('#errores');
        erroresDiv.innerHTML = '';

        try {
            const response = await fetch(`${this.srvUrl}/${id}`, {
                method: 'DELETE'
            });

            if (response.ok) {
                erroresDiv.innerHTML = '<p class="text-success">Usuario eliminado correctamente.</p>';
                this.cargaUsuarios();
            } else {
                const error = await response.json();
                erroresDiv.innerHTML = `<p class="text-danger">Error al eliminar el usuario: ${error.message || response.status}</p>`;
            }
        } catch (err) {
            erroresDiv.innerHTML = `<p class="text-danger">Error de conexión: ${err.message}</p>`;
        }
    }

    async mostrarDetalle(id) {
        const detalleDiv = el('#detalle');
        const detalleContenido = el('#detalleContenido');
        detalleContenido.innerHTML = '';

        try {
            const response = await fetch(`${this.srvUrl}/${id}`);
            if (!response.ok) throw new Error("No se pudo cargar el detalle");

            const usuario = await response.json();

            detalleContenido.innerHTML = `
            <li class="list-group-item"><strong>Nombre:</strong> ${usuario.nombre}</li>
            <li class="list-group-item"><strong>Usuario:</strong> ${usuario.usuario}</li>
            <li class="list-group-item"><strong>Email:</strong> ${usuario.email}</li>
            <li class="list-group-item"><strong>DNI:</strong> ${usuario.dni}</li>
            <li class="list-group-item"><strong>Teléfono:</strong> ${usuario.telefono}</li>
            <li class="list-group-item"><strong>Dirección:</strong> ${usuario.direccion}</li>
            <li class="list-group-item"><strong>Fecha Nacimiento:</strong> ${usuario.fechaNacimiento}</li>
            <li class="list-group-item"><strong>Tarjeta:</strong> ${usuario.numeroDeTarjeta}</li>
        `;

            detalleDiv.style.display = "block";

        } catch (err) {
            detalleContenido.innerHTML = `<li class="list-group-item text-danger">Error al cargar detalle: ${err.message}</li>`;
            detalleDiv.style.display = "block";
        }
    }
}


window.addEventListener('load', () => {
    window.ctrl = new UsuariosCtrl();
    ctrl.init();
});