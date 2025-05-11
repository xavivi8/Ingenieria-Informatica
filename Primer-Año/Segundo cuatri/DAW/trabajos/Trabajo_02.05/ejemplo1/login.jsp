<%@taglib prefix="tag" tagdir="/WEB-INF/tags" %>
<%@ taglib prefix="th" uri="http://www.springframework.org/tags/form" %>
<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Inicio de Sesión</title>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.2/dist/css/bootstrap.min.css">
</head>
<body>
<tag:header/>
<div class="row justify-content-center w-100" style="height: 100%; padding: 0px 50px 0px 50px; margin:0;">
    <div class="col-lg-5">
        <div class="border rounded p-4 shadow">
            <h3 class="text-center mb-4">INICIO DE SESIÓN</h3>
            <form id="formLogin" method="POST" action="/loginUser">
                <fieldset>
                    <div class="mb-3">
                        <label for="username">Correo electrónico</label>
                        <input type="text" class="form-control" id="username" name="username" placeholder="Ingresa tu correo electrónico" value="${email}" required>
                    </div>
                    <div class="mb-3">
                        <label for="password">Contraseña</label>
                        <input type="password" class="form-control" id="password" name="password" placeholder="Ingresa tu contraseña" value="${contrasena}" required>
                    </div>
                    <c:if test="${param.error eq 'true'}">
                        <div class="alert alert-danger">Usuario o contraseña incorrectos.</div>
                    </c:if>
                </fieldset>
                <div class="d-grid">
                    <input type="submit" class="btn btn-primary" value="Entrar">
                </div>
                <div class="text-center mt-3">
                    <p>Si no estás registrado, <a href="<c:url value='/usuarios/form'/>">regístrate</a></p>
                </div>
            </form>
        </div>
    </div>
</div>
</body>
</html>
