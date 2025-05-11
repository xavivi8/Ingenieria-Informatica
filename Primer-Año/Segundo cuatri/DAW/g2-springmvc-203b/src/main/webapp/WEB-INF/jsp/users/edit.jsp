<%--
  Created by IntelliJ IDEA.
  User: jmart
  Date: 11/04/2025
  Time: 15:19
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@ taglib prefix="tagg" tagdir="/WEB-INF/tags/templates" %>

<html>
<head>
    <meta charset="UTF-8">
    <title>Editar Usuario</title>
</head>
<body>
<tagg:header-web/>
<main class="d-flex">
    <tagg:nav-web/>
    <div class="container-fluid ms-3" id="contenido-principal">
        <h2 class="mb-4">Editar Usuario</h2>

        <!-- Formulario con validación de Spring -->
        <form:form method="POST" action="${srvUrl}/edit" modelAttribute="user" class="well">

        <!-- ID (oculto) -->
            <form:input path="id" type="hidden" />

            <!-- Nombre -->
            <div class="mb-3">
                <form:label path="name" class="form-label">Nombre</form:label>
                <form:input path="name" class="form-control"/>
                <form:errors path="name" cssClass="text-danger"/>
            </div>

            <!-- Apellido -->
            <div class="mb-3">
                <form:label path="surname" class="form-label">Apellidos</form:label>
                <form:input path="surname" class="form-control"/>
                <form:errors path="surname" cssClass="text-danger"/>
            </div>

            <!-- DNI -->
            <div class="mb-3">
                <form:label path="dni" class="form-label">DNI</form:label>
                <form:input path="dni" class="form-control"/>
                <form:errors path="dni" cssClass="text-danger"/>
            </div>

            <!-- Correo electrónico -->
            <div class="mb-3">
                <form:label path="email" class="form-label">Correo electrónico</form:label>
                <form:input path="email" class="form-control"/>
                <form:errors path="email" cssClass="text-danger"/>
            </div>

            <!-- Contraseña -->
            <div class="mb-3">
                <form:label path="password" class="form-label">Contraseña</form:label>
                <form:password path="password" class="form-control" value="${user.password}"/>
                <form:errors path="password" cssClass="text-danger"/>
            </div>


            <!-- Teléfono -->
            <div class="mb-3">
                <form:label path="phone" class="form-label">Teléfono</form:label>
                <form:input path="phone" class="form-control"/>
                <form:errors path="phone" cssClass="text-danger"/>
            </div>

            <!-- Foto -->
            <div class="mb-3">
                <form:label path="photo" class="form-label">Foto (opcional)</form:label>
                <form:input path="photo" class="form-control"/>
                <form:errors path="photo" cssClass="text-danger"/>
            </div>

            <!-- Rol -->
            <div class="mb-3">
                <form:label path="role" class="form-label">Rol</form:label>
                <form:select path="role" class="form-select">
                    <form:option value="ADMIN">Administrador</form:option>
                    <form:option value="RRHH">RRHH</form:option>
                    <form:option value="EMPLOYEE">Empleado</form:option>
                </form:select>
                <form:errors path="role" cssClass="text-danger"/>
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

