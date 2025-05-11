<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="jakarta.tags.core" prefix="c" %>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Lista de Usuarios (MVC)</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css"
          rel="stylesheet"
          integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH"
          crossorigin="anonymous">
    <style>
        body { font-family: 'Inter', sans-serif; padding-top: 20px; }
        .container { max-width: 900px; }
        .table th, .table td { vertical-align: middle; }
        .action-buttons form { display: inline-block; margin-left: 5px; }
        .action-buttons .btn { margin-left: 0.25rem;}
    </style>
</head>
<body>
<div class="container">
    <div class="d-flex justify-content-between align-items-center mb-4">
        <h1>Gestión de Usuarios (Jakarta MVC)</h1>
        <%-- El contextPath es importante si la app no está en la raíz --%>
        <a href="${pageContext.request.contextPath}/mvc/usuarios/add" class="btn btn-primary rounded-pill">
            Añadir Nuevo Usuario
        </a>
    </div>

    <%-- Mensajes de éxito (leídos de 'models' que a su vez los tomó de query params) --%>
    <c:if test="${not empty models.successMessage || not empty param.success}">
        <div class="alert alert-success alert-dismissible fade show rounded-3" role="alert">
            <c:set var="msgKey" value="${not empty models.successMessage ? models.successMessage : param.success}" />
            <c:choose>
                <c:when test="${msgKey == 'UsuarioCreado'}">Usuario creado correctamente.</c:when>
                <c:when test="${msgKey == 'UsuarioActualizado'}">Usuario actualizado correctamente.</c:when>
                <c:when test="${msgKey == 'UsuarioEliminado'}">Usuario eliminado correctamente.</c:when>
                <c:otherwise>Operación realizada con éxito: <c:out value="${msgKey}"/></c:otherwise>
            </c:choose>
            <button type="button" class="btn-close" data-bs-dismiss="alert" aria-label="Close"></button>
        </div>
    </c:if>

    <%-- Mensajes de errores --%>
    <c:if test="${not empty models.errorMessage || not empty param.error}">
        <div class="alert alert-danger alert-dismissible fade show rounded-3" role="alert">
            <c:set var="errKey" value="${not empty models.errorMessage ? models.errorMessage : param.error}" />
            <c:choose>
                <c:when test="${errKey == 'UsuarioNoEncontrado'}">Error: Usuario no encontrado.</c:when>
                <c:when test="${errKey == 'ErrorAlEliminar'}">Error: No se pudo eliminar el usuario.</c:when>
                <c:otherwise>Ocurrió un error: <c:out value="${errKey}"/></c:otherwise>
            </c:choose>
            <button type="button" class="btn-close" data-bs-dismiss="alert" aria-label="Close"></button>
        </div>
    </c:if>

    <div class="card shadow-sm rounded-3">
        <div class="card-body">
            <c:choose>
                <c:when test="${not empty models.listaUsuarios}">
                    <table class="table table-hover">
                        <thead class="table-light">
                        <tr>
                            <th>ID</th>
                            <th>Nombre</th>
                            <th>Email</th>
                            <th class="text-end">Acciones</th>
                        </tr>
                        </thead>
                        <tbody>
                        <c:forEach var="usuario" items="${models.listaUsuarios}">
                            <tr>
                                <td><c:out value="${usuario.id}"/></td>
                                <td><c:out value="${usuario.nombre}"/></td>
                                <td><c:out value="${usuario.email}"/></td>
                                <td class="text-end action-buttons">
                                    <a href="${pageContext.request.contextPath}/mvc/usuarios/edit/${usuario.id}"
                                       class="btn btn-sm btn-outline-primary rounded-pill">Editar</a>

                                    <form action="${pageContext.request.contextPath}/mvc/usuarios/delete/${usuario.id}" method="post" style="display: inline;">
                                        <button type="submit" class="btn btn-sm btn-outline-danger rounded-pill" onclick="return confirm('¿Estás seguro de que quieres eliminar este usuario?');">Eliminar </button>
                                    </form>
                                </td>
                            </tr>
                        </c:forEach>
                        </tbody>
                    </table>
                </c:when>
                <c:otherwise>
                    <p class="text-center text-muted">No hay usuarios para mostrar.</p>
                </c:otherwise>
            </c:choose>
        </div>
    </div>
    <footer class="text-center mt-4 text-muted">
        <p>&copy; ${java.time.Year.now()} Mi Aplicación CRUD con MVC</p>
    </footer>
</div>

<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz"
        crossorigin="anonymous"></script>
</body>
</html>

