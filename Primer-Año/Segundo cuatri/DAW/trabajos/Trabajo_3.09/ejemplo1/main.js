// Registro del Service Worker
if ('serviceWorker' in navigator) {
    window.addEventListener('load', () => {
        navigator.serviceWorker.register('./service-worker.js')

            .then(() => console.log('ServiceWorker registrado'))
            .catch(err => console.error('Error al registrar el SW:', err));
    });
}

// Detectar cambios en el estado de conexión
const statusEl = document.getElementById('status').querySelector('span');
function updateOnlineStatus() {
    statusEl.textContent = navigator.onLine ? 'En línea' : 'Offline';
}
window.addEventListener('online', updateOnlineStatus);
window.addEventListener('offline', updateOnlineStatus);
// Inicializar estado al cargar
updateOnlineStatus();
