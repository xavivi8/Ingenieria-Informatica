const CACHE_NAME = 'tareas-cache-v1';
const URLS_A_CACHEAR = [
    '/',
    '/index.html',
    '/estilos/style.css',
    '/app.js',
    '/manifest.json',
    '/icons/',
    '/icons/icon-192.png'
];

self.addEventListener('install', e => {
    e.waitUntil(
        caches.open(CACHE_NAME).then(cache => cache.addAll(URLS_A_CACHEAR))
    );
});

self.addEventListener('fetch', e => {
    e.respondWith(
        caches.match(e.request).then(resp => resp || fetch(e.request))
    );
});
