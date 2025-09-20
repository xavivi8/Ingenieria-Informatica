<template>
    <header class="bg-primary text-white position-fixed shadow w-100 p-3 d-flex align-items-center justify-content-between">
        <!-- Zona izquierda vacía -->
        <div style="width: 70px;"></div>
        <!-- Centro con logo y texto -->
        <div class="d-flex align-items-center justify-content-center">
            <img src="../assets/logo.svg" styleClass="rounded-circle border"
                style="width: 40px; height: 40px; object-fit: cover;" />
            <h2 class="fw-bold m-0 ms-3">CRM</h2>
        </div>

        <!-- Botón logout -->
        <div>
            <div class="dropdown">
                <!-- Imagen como botón para desplegar -->
                <a class="btn dropdown-toggle p-0 border-0 bg-transparent" href="#">
                    <img src="../assets/img/poro.jpg" styleClass="rounded-circle border"
                        style="width: 40px; height: 40px; object-fit: cover;" />
                </a>

                <!-- Menú desplegable -->
                <ul class="dropdown-menu dropdown-menu-end" aria-labelledby="dropdownMenuButton">
                    <li>
                        <a href="#" styleClass="dropdown-item">
                            Perfil
                        </a>
                    </li>
                    <li>
                            <a href="#" styleClass="dropdown-item">
                                Cerrar sesión
                            </a>
                    </li>
                </ul>
            </div>
        </div>
    </header>
</template>