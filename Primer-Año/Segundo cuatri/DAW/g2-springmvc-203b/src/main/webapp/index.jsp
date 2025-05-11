<%@ page contentType="text/html;charset=UTF-8" %>
<%@taglib prefix="fmt" uri="jakarta.tags.fmt" %>
<%@taglib prefix="c" uri="jakarta.tags.core" %>
<%@ taglib prefix="tagg" tagdir="/WEB-INF/tags/templates" %>
<fmt:setBundle basename="messages"/>
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <title><fmt:message key="appName"/></title>

</head>
<body>
<tagg:header-web/>
<div class="container d-flex justify-content-center align-items-center" style="height: 100vh;">
    <main class="text-center">
        <a href="<c:url value="/users"/>" class="btn btn-primary w-50">Acceder</a>
    </main>
</div>
<tagg:footer-web/>
</body>
</html>
