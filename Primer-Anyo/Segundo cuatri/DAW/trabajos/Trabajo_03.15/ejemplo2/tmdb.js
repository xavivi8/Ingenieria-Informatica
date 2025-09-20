const TMDB_API_KEY = '9adfb83b70a325dceefd070ab7da2146';

function buscarPelicula(nombre, callback) {
    axios.get('https://api.themoviedb.org/3/search/movie', {
        params: { api_key: TMDB_API_KEY, query: nombre }
    })
        .then(response => callback(response.data.results))
        .catch(error => console.error('Error al buscar película:', error));
}

function mostrarResultadosTMDB(peliculas) {
    const contenedor = document.getElementById('resultados-tmdb');
    contenedor.innerHTML = ''; // limpia resultados previos

    peliculas.forEach(peli => {
        const col = document.createElement('div');
        col.className = 'col';

        col.innerHTML = `
          <div class="card movie-card h-100 shadow-sm">
              <img
                src="https://image.tmdb.org/t/p/w500${peli.poster_path}"
                alt="${peli.title}"
                class="card-img-top movie-img"
              />
              <div class="card-body">
                <p class="card-text">${peli.title}</p>
              </div>
            </a>
          </div>
        `;

        contenedor.appendChild(col);
    });
}



