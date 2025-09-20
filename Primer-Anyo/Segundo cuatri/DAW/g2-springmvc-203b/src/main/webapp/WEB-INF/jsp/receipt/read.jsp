<%@ page contentType="text/html;charset=UTF-8" %>
<%@taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="templates" tagdir="/WEB-INF/tags/templates" %>
<!DOCTYPE html>
<html lang="es">
    <head>
        <meta charset="UTF-8">
        <title>Visualiza Factura </title>
        <%@include file="/WEB-INF/layout/bootstrapheader.jspf"%>
    </head>
    <body class="container">
    <templates:header-web/>
        <main class="row">
            <nav class="col-md-3">
                <h2>Opciones</h2>
                <ul class="nav nav-pills flex-column">
                    <li class="nav-item">
                        <a href='<c:url value="/receipts/edit?id=${receipt.id}"/>' class="nav-link">Editar</a>
                    </li>
                    <li class="nav-item">
                        <a href='<c:url value="/home"/>' class="nav-link">Volver</a>
                    </li>
                </ul>
            </nav>   
            <section class="col-md-9">
                <div class="panel panel-default">
                    <h2 class="panel-heading">Datos Factura</h2>
                    <ul class="panel-body list-group">
                        <li class="list-group-item"><strong>ID:</strong>
                            <span class="list-group-item-text">${receipt.id}</span>
                        </li>
                        <li class="list-group-item">
                            <strong>Persona responsable:</strong> ${receipt.userCrm}
                        </li>
                        <li class="list-group-item">
                            <strong>Cantidad a pagar:</strong> ${receipt.amount}
                        </li>
                    </ul>
                </div>
            </section>
            </main>
    <templates:footer-web/>
</body>
</html>