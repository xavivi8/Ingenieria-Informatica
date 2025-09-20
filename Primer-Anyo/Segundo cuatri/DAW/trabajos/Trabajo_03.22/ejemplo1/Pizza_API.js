const fs = require('fs');
const path = require('path');

const cachePath = path.join(__dirname, 'pizzas_cache.json');

window.addEventListener('DOMContentLoaded', () => {
    const ul = document.getElementById('pizza-list');

    fetch('http://localhost:8080/app/api/pizzas')
        .then(res => {
            if (!res.ok) throw new Error("Error al conectar con el backend");
            return res.json();
        })
        .then(pizzas => {
            renderPizzas(pizzas, ul);
            saveToCache(pizzas);
        })
        .catch(err => {
            console.warn("No se pudo conectar al backend. Cargando desde caché.");
            loadFromCache(ul);
        });
});

function renderPizzas(pizzas, ul) {
    ul.innerHTML = '';

    if (!pizzas || pizzas.length === 0) {
        ul.innerHTML = '<li>No se encontraron pizzas.</li>';
        return;
    }

    pizzas.forEach(pizza => {
        const li = document.createElement('li');
        li.innerHTML = `
            <div class="pizza-item">
                <img src="http://localhost:8080/app/${pizza.imagen}" alt="${pizza.nombre}">
                <div class="pizza-details">
                    <h3>${pizza.nombre} (${pizza.tamanio})</h3>
                    <p><strong>Precio:</strong> €${pizza.precio.toFixed(2)}</p>
                    <p><strong>Masa:</strong> ${pizza.tipoMasa}</p>
                    <p><strong>Ingredientes:</strong> ${pizza.ingredientes.join(', ')}</p>
                    <p><strong>Descripción:</strong> ${pizza.descripcion}</p>
                    </div>
            </div>
        `;
        ul.appendChild(li);
    });
}

function saveToCache(pizzas) {
    fs.writeFileSync(cachePath, JSON.stringify(pizzas, null, 2), 'utf8');
}

function loadFromCache(ul) {
    if (fs.existsSync(cachePath)) {
        const data = fs.readFileSync(cachePath, 'utf8');
        const pizzas = JSON.parse(data);
        renderPizzas(pizzas, ul);
    } else {
        ul.innerHTML = '<li>No hay datos disponibles en caché</li>';
    }

}
