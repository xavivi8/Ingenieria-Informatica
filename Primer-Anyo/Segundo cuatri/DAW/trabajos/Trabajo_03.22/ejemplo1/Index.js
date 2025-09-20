document.addEventListener("DOMContentLoaded", () => {
    const registroLink = document.getElementById("registro-link");

    if (registroLink) {
        registroLink.addEventListener("click", (e) => {
            e.preventDefault();

            fetch("http://localhost:8080/app/", { method: 'HEAD' })
                .then(response => {
                    if (response.ok) {
                        window.location.href = "http://localhost:8080/app/LoginCrearCuenta.xhtml";
                    } else {
                        window.location.href = "Error404.html";
                    }
                })
                .catch(() => {
                    window.location.href = "Error404.html";
                });
        });
    }
});
