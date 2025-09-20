<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="tagg" tagdir="/WEB-INF/tags/templates" %>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Alta Factura</title>
        <%@include file="/WEB-INF/layout/bootstrapheader.jspf"%>
    </head>
    <body class="container">

        <tagg:header-web/>

        <main class="d-flex">
            <nav class="col-md-3">
                <h2>Opciones</h2>
                <ul class="nav nav-pills flex-column">
                    <li class="nav-item"><crm:logout-button/></li>
                    <li class="nav-item"><a class="nav-link" href="home">Volver</a></li>

                </ul>
            </nav>
            <tagg:nav-web/>
            <div class="container-fluid ms-3" id="contenido-principal">
                <h2 class="mb-4">Añadir Nueva Factura</h2>
                <form:errors path="receipt.*" cssClass="text-danger" element="div" />
                <form:form method="POST" class="well" modelAttribute="receipt">

                    <!-- Usuario CRM -->
                    <div class="mb-3">
                        <form:label path="userCrm" class="form-label">Responsable</form:label>
                        <form:input path="userCrm" class="form-control"/>
                        <form:errors path="userCrm" cssClass="text-danger"/>
                    </div>
                    <div><form:errors cssClass="form-text text-danger" path="userCrm"/></div>

                    <!-- Precio total -->
                    <div class="mb-3">
                        <form:label path="amount" class="form-label">Cantidad total</form:label>
                        <form:input path="amount" class="form-control"/>
                        <form:errors path="amount" cssClass="text-danger"/>
                    </div>
                    <div><form:errors cssClass="form-text text-danger" path="amount"/></div>

                    <!-- Botones de acción -->
                    <div>
                        <input name="enviar" type="Submit" value="Guardar" class="btn btn-primary">
                        <input name="enviar" type="reset" value="Limpiar" class="btn btn-default">
                        <a class="btn btn-default" href="home">Volver</a>
                    </div>
                </form:form>
            </div>
        </main>

        <tagg:footer-web/>
    </body>
</html>