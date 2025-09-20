<%--
  Created by IntelliJ IDEA.
  User: jmart
  Date: 11/04/2025
  Time: 16:47
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="tagg" tagdir="/WEB-INF/tags/templates" %>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Listado de Productos</title>
    <%@ include file="/WEB-INF/layout/bootstrapheader.jspf" %>
</head>
<body>
<tagg:header-web/>
<main class="d-flex">
    <tagg:nav-web/>
    <div class="container-fluid ms-3" id="contenido-principal">

        <div class="container mt-4">
            <h2 class="text-center">Listado de Productos</h2>
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
            <c:if test="${empty productos}">
                No hay productos registrados.
            </c:if>
            <c:if test="${not empty productos}">
                <table class="table table-striped">
                    <thead>
                    <tr>
                        <th>ID</th>
                        <th>Nombre</th>
                        <th>Stock</th>
                        <th>Precio Base</th>
                        <th>Acciones</th>
                    </tr>
                    </thead>
                    <tbody>
                    <c:forEach items="${productos}" var="producto">
                        <tr>
                            <td>${producto.id}</td>
                            <td>${producto.name}</td>
                            <td>${producto.stock}</td>
                            <td>${producto.base_price}</td>
                            <td>
                                <!-- Botón para eliminar -->
                                <form action="${srvUrl}/delete" method="get" onsubmit="return confirmarEliminacion()">
                                    <input type="hidden" name="id" value="${producto.id}"/>
                                    <button type="submit" class="btn btn-danger">
                                        Eliminar
                                    </button>
                                </form>
                                <!-- Botón para editar -->
                                <form action="${srvUrl}/edit" method="get">
                                    <input type="hidden" name="id" value="${producto.id}"/>
                                    <button type="submit" class="btn btn-warning">
                                        Editar
                                    </button>
                                </form>
                                <script>
                                    function confirmarEliminacion() {
                                        return confirm("¿Estás seguro de que quieres eliminar este producto?");
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