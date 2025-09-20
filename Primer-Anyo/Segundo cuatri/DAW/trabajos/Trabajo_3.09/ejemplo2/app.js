const input = document.getElementById('nueva-tarea');
const lista = document.getElementById('lista-tareas');

function cargarTareas() {
    const tareas = JSON.parse(localStorage.getItem('tareas') || '[]');
    lista.innerHTML = '';
    tareas.forEach((t, i) => {
        const li = document.createElement('li');
        li.textContent = t;
        li.onclick = () => eliminarTarea(i);
        lista.appendChild(li);
    });
}

function agregarTarea() {
    const tarea = input.value.trim();
    if (tarea !== '') {
        const tareas = JSON.parse(localStorage.getItem('tareas') || '[]');
        tareas.push(tarea);
        localStorage.setItem('tareas', JSON.stringify(tareas));
        input.value = '';
        cargarTareas();
    }
}

function eliminarTarea(i) {
    const tareas = JSON.parse(localStorage.getItem('tareas') || '[]');
    tareas.splice(i, 1);
    localStorage.setItem('tareas', JSON.stringify(tareas));
    cargarTareas();
}

cargarTareas();
