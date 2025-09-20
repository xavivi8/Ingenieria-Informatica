function modificarCantidad(btn, cambio) {
    let cantidadSpan = btn.parentElement.querySelector(".cantidad");
    let cantidad = parseInt(cantidadSpan.textContent);
    cantidad = Math.max(0, cantidad + cambio);
    cantidadSpan.textContent = cantidad;
}

function editarArticulo(btn) {
    let li = btn.closest("li");
    let nombreSpan = li.querySelector("span");
    let nuevoNombre = prompt("Nuevo nombre del artículo:", nombreSpan.textContent);
    if (nuevoNombre) {
        nombreSpan.textContent = nuevoNombre;
    }
}

function eliminarArticulo(btn) {
    let li = btn.closest("li");
    li.remove();
}