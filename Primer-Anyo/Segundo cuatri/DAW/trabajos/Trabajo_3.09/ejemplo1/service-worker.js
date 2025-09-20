const CACHE_NAME = 'hola-pwa-v1';
const URLS_TO_CACHE = [
    './',
    './index.html',
    './main.js'
    // Nota: se podrían incluir iconos u otros recursos si se desea cachearlos
];

// Instalación: cachear la app shell
self.addEventListener('install', event => {
    console.log('Service Worker: Instalando y cacheando recursos...');
    event.waitUntil(
        caches.open(CACHE_NAME).then(cache => {
            return cache.addAll(URLS_TO_CACHE);
        })
    );
});

// Activación: limpiar caches antiguas (si hubiera versiones previas)
self.addEventListener('activate', event => {
    event.waitUntil(
        caches.keys().then(keys => {
            // Borrar caches que no coincidan con CACHE_NAME actual
            return Promise.all(
                keys.filter(key => key !== CACHE_NAME)
                    .map(key => caches.delete(key))
            );
        })
    );
});

// Intercepción de fetch: responder con recursos cacheados cuando sea posible
self.addEventListener('fetch', event => {
    // Solo interceptamos peticiones GET de nuestro dominio
    if (event.request.method !== 'GET') return;
    event.respondWith(
        caches.match(event.request).then(response => {
            // Si el recurso está en caché, lo devuelve; sino, lo pide a la red
            return response || fetch(event.request);
        })
    );
});
