const fs = require('fs');
const path = require('path');

const cachePath = path.join(__dirname, 'curriculums_cache.json');

window.addEventListener('DOMContentLoaded', () => {
    const ul = document.getElementById('cv-list');

    fetch('http://localhost:8080/app/api/curriculums')
        .then(res => {
            if (!res.ok) throw new Error("Error al conectar con el backend");
            return res.json();
        })
        .then(curriculums => {
            renderCurriculums(curriculums, ul);
            saveToCache(curriculums);
        })
        .catch(err => {
            console.warn("No se pudo conectar al backend. Cargando desde caché.");
            loadFromCache(ul);
        });
});

function renderCurriculums(curriculums, ul) {
    ul.innerHTML = '';

    if (!curriculums || curriculums.length === 0) {
        ul.innerHTML = '<li>No se encontraron currículums.</li>';
        return;
    }

    curriculums.forEach(cv => {
        const li = document.createElement('li');
        li.innerHTML = `
            <div class="cv-item">
                <div class="cv-details">
                    <h3>${cv.nombre}</h3>
                    <p><strong>Email:</strong> ${cv.email}</p>
                    <p><strong>Teléfono:</strong> ${cv.telefono}</p>
                    <p><strong>Dirección:</strong> ${cv.direccion}</p>
                    <p><a href="http://localhost:8080/app${cv.cvPath}" target="_blank" class="cv-link">Ver CV (PDF)</a></p>
                </div>
            </div>
        `;
        ul.appendChild(li);
    });
}

function saveToCache(curriculums) {
    fs.writeFileSync(cachePath, JSON.stringify(curriculums, null, 2), 'utf8');
}

function loadFromCache(ul) {
    if (fs.existsSync(cachePath)) {
        const data = fs.readFileSync(cachePath, 'utf8');
        const curriculums = JSON.parse(data);
        renderCurriculums(curriculums, ul);
    } else {
        ul.innerHTML = '<li>No hay datos disponibles en caché</li>';
    }
}
