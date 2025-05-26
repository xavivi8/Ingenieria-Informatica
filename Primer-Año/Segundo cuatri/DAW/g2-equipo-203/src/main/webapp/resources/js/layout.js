/* Articulos */
document.getElementById('btn-articulos').addEventListener('click', function(event) {
    event.preventDefault();  // Prevenir el comportamiento por defecto del enlace

    fetch('/app/articulos/articulos.xhtml')  // Ruta correcta al archivo articulos.css.html
        .then(response => response.text())
        .then(data => {
            document.getElementById('contenido-principal').innerHTML = data;  // Reemplazar el contenido
        })
        .catch(error => {
            console.error('Error al cargar el contenido:', error);
        });
});

/* Empleados */
document.getElementById('btn-empleados').addEventListener('click', function(event) {
    event.preventDefault();

    fetch('/app/Empleados/html/Empleados.html')
        .then(response => response.text())
        .then(data => {
            document.getElementById('contenido-principal').innerHTML = data;  // Reemplazar el contenido
        })
        .catch(error => {
            console.error('Error al cargar el contenido:', error);
        });
});

/* Facturas */
document.getElementById('btn-facturas').addEventListener('click', function(event) {
    event.preventDefault();

    fetch('/app/Facturas/html/factura.html')
        .then(response => response.text())
        .then(data => {
            document.getElementById('contenido-principal').innerHTML = data;  // Reemplazar el contenido
        })
        .catch(error => {
            console.error('Error al cargar el contenido:', error);
        });
});

/* Nominas */
document.getElementById('btn-nominas').addEventListener('click', function(event) {
    event.preventDefault();

    fetch('/app/Nominas/html/nominas.html')
        .then(response => response.text())
        .then(data => {
            document.getElementById('contenido-principal').innerHTML = data;  // Reemplazar el contenido
        })
        .catch(error => {
            console.error('Error al cargar el contenido:', error);
        });
});