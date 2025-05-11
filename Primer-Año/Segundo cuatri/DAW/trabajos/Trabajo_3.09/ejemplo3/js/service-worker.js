const CACHE_NAME = 'calculadora-propina-v1';
const URLS_A_CACHEAR = [
    '/',
    '/index.html',
    '/estilos/style.css',
    '/js/app.js',
    '/js/service-worker.js',
    '/manifest.json',
    '/icons/',
    '/icons/img.png'
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
