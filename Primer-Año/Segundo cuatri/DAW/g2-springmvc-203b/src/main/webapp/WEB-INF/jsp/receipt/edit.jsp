<%@ page contentType="text/html;charset=UTF-8" %>
<%@taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="templates" tagdir="/WEB-INF/tags/templates" %>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Edita Factura</title>
    <%@include file="/WEB-INF/layout/bootstrapheader.jspf" %>
</head>
<body class="container">
<templates:header-web/>
<main class="row">
    <nav class="col-md-3">
        <h2>Opciones</h2>
        <ul class=" nav nav-pills flex-column">
            <li class="nav-item"><a href="home">Volver</a></li>
        </ul>
    </nav>
    <section class="col-md-6">
        <h1>Editar Factura</h1>
        <form:form method="POST" modelAttribute="receipt" cssClass="well">

            <h3>Receipt IDENTIFICADOR: ${receipt.id}</h3>

            <form:label path="userCrm">Persona responsable:</form:label>
            <form:input class='form-control' path="userCrm"/>
            <div><form:errors cssClass="form-text text-danger" path="userCrm"/></div>

            <form:label path="amount">Cantidad total:</form:label>
            <form:input path="amount" cssClass="form-control"/>
            <div><form:errors cssClass="form-text text-danger" path="amount"/></div>

            <p>
                <input class="btn btn-primary" name="enviar" type="Submit" value="Guardar">
                <input class="btn btn-default" name="enviar" type="Reset" value="Limpiar">
                <a class="btn btn-default" href="listado">Volver</a>
            </p>
        </form:form>
    </section>
</main>

<templates:footer-web/>
</body>
</html>