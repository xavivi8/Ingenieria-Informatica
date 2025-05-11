<%--
  Created by IntelliJ IDEA.
  User: jmart
  Date: 11/04/2025
  Time: 17:15
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@ taglib prefix="tagg" tagdir="/WEB-INF/tags/templates" %>

<html>
<head>
    <meta charset="UTF-8">
    <title>Editar Producto</title>
</head>
<body>
<tagg:header-web/>
<main class="d-flex">
    <tagg:nav-web/>
    <div class="container-fluid ms-3" id="contenido-principal">
        <h2 class="mb-4">Editar Producto</h2>

        <!-- Formulario con validación de Spring -->
        <form:form method="POST" action="${srvUrl}/edit" modelAttribute="product" class="well">

            <!-- ID (oculto) -->
            <form:input path="id" type="hidden" />

            <!-- Nombre -->
            <div class="mb-3">
                <form:label path="name" class="form-label">Nombre</form:label>
                <form:input path="name" class="form-control"/>
                <form:errors path="name" cssClass="text-danger"/>
            </div>

            <!-- Descripción -->
            <div class="mb-3">
                <form:label path="description" class="form-label">Descripción</form:label>
                <form:input path="description" class="form-control"/>
                <form:errors path="description" cssClass="text-danger"/>
            </div>

            <!-- Precio Base -->
            <div class="mb-3">
                <form:label path="base_price" class="form-label">Precio Base</form:label>
                <form:input path="base_price" class="form-control"/>
                <form:errors path="base_price" cssClass="text-danger"/>
            </div>

            <!-- Stock -->
            <div class="mb-3">
                <form:label path="stock" class="form-label">Stock</form:label>
                <form:input path="stock" class="form-control"/>
                <form:errors path="stock" cssClass="text-danger"/>
            </div>

            <!-- Botones de acción -->
            <div>
                <input type="submit" value="Guardar Cambios" class="btn btn-success"/>
                <a href="${srvUrl}/home" class="btn btn-default">Volver</a>
            </div>
        </form:form>
    </div>
</main>
<tagg:footer-web/>
</body>
</html>