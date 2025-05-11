<%@ page contentType="text/html;charset=UTF-8" %>
<%@taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="tagg" tagdir="/WEB-INF/tags/templates" %>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Listado de Usuarios</title>
    <%@include file="/WEB-INF/layout/bootstrapheader.jspf" %>
</head>
<body>
<tagg:header-web/>
<main class="d-flex">
    <tagg:nav-web/>
    <div class="container-fluid ms-3" id="contenido-principal">

        <div class="container mt-4">
            <h2 class="text-center">Listado de Usuarios</h2>
            <div class="row mb-3">
                <div class="col-md-8 mx-auto d-flex">
                    <label>
                        <input type="text" class="form-control me-2" placeholder="Buscar..."/>
                    </label>
                    <form action="${srvUrl}/add" method="get">
                        <button type="submit" class="btn btn-primary">
                            <i class="bi bi-plus-lg"/> Agregar
                        </button>
                    </form>

                </div>
            </div>
        </div>

        <div>
            <c:if test="${empty usuarios}">
                No hay usuarios registrados.
            </c:if>
            <c:if test="${not empty usuarios}">
                <table class="table table-striped">
                    <thead>
                    <tr>
                        <th>ID</th>
                        <th>DNI</th>
                        <th>Email</th>
                        <th>Nombre</th>
                        <th>Apellido</th>
                        <th>Teléfono</th>
                        <th>Rol</th>
                        <th>Acciones</th>
                    </tr>
                    </thead>
                    <tbody>
                    <c:forEach items="${usuarios}" var="usuario">
                        <tr>
                            <td>${usuario.id}</td>
                            <td>${usuario.dni}</td>
                            <td>${usuario.email}</td>
                            <td>${usuario.name}</td>
                            <td>${usuario.surname}</td>
                            <td>${usuario.phone}</td>
                            <td>${usuario.role}</td>
                            <td>
                                <!-- Botón para eliminar -->
                                <form action="${srvUrl}/delete" method="get" onsubmit="return confirmarEliminacion()">
                                    <input type="hidden" name="id" value="${usuario.id}"/>
                                    <button type="submit" class="btn btn-danger">
                                        Eliminar
                                    </button>
                                </form>
                                <!-- Botón para editar -->
                                <form action="${srvUrl}/edit" method="get">
                                    <input type="hidden" name="id" value="${usuario.id}"/>
                                    <button type="submit" class="btn btn-warning">
                                        Editar
                                    </button>
                                </form>
                                <script>
                                    function confirmarEliminacion() {
                                        return confirm("¿Estás seguro de que quieres eliminar a este usuario?");
                                    }
                                </script>
                            </td>
                        </tr>
                    </c:forEach>
                    </tbody>
                </table>
            </c:if>

        </div>

    </div>
</main>
<tagg:footer-web/>
</body>
</html>