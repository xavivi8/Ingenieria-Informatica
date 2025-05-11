<%@ taglib prefix="c" uri="jakarta.tags.core" %>
<%@ include file="/WEB-INF/layout/bootstrapheader.jspf" %>
<nav class="bg-light p-3" id="sidebar" style="width: 250px;">
    <h4>Menu</h4>
    <ul class="nav flex-column">
        <li class="nav-item">
            <a href="<c:url value="/users"/>" class="nav-link">Usuarios</a>
        </li>
        <li class="nav-item">
            <a href="<c:url value="/products"/>" class="nav-link">Productos</a>
        </li>
        <li class="nav-item">
            <a href="<c:url value="/receipts"/>" class="nav-link">Facturas</a>
        </li>
    </ul>
</nav>
