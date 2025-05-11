<%@ page contentType="text/html;charset=UTF-8" %>
<%@taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="tagg" tagdir="/WEB-INF/tags/templates" %>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title>Listado de Facturas</title>
    <link rel="stylesheet" type="text/css" href="<c:url value='/css/common.css'/>">
    <%@include file="/WEB-INF/layout/bootstrapheader.jspf" %>
</head>
<body>
<tagg:header-web/>
<main class="d-flex">
    <tagg:nav-web/>
    <div class="container-fluid ms-3" id="contenido-principal">

        <div class="container mt-4">
            <h2 class="text-center">Listado de Facturas</h2>
            <div class="row mb-3">
                <div class="col-md-8 mx-auto d-flex">
                    <label>
                        <input type="text" class="form-control me-2" placeholder="Buscar..."/>
                    </label>
                    <button class="btn btn-primary">
                        <i class="bi bi-plus-lg"/>Añadir
                    </button>
                </div>
            </div>
        </div>

        <div>
            <c:if test="${empty receipts}">
                No hay facturas registradas.
            </c:if>
            <c:if test="${not empty receipts}">
                <table class="table table-striped">
                    <thead>
                    <tr>
                        <th>ID</th>
                    </tr>
                    </thead>
                    <tbody>
                    <c:forEach items="${receipts}" var="receipt">
                        <tr>
                            <td>${receipt.id}</td>
                            <td>
                                <!-- Aquí puedes agregar botones para editar o eliminar usuarios -->
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