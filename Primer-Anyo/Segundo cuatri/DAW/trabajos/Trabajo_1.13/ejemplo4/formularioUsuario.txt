<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="jakarta.tags.core" prefix="c" %>
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <%-- El título cambia según si es 'add' o 'edit' --%>
  <title>${models.formAction == 'add' ? 'Añadir' : 'Editar'} Usuario (MVC)</title>
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css"
        rel="stylesheet"
        integrity="sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH"
        crossorigin="anonymous">
  <style>
    body { font-family: 'Inter', sans-serif; padding-top: 20px; background-color: #f8f9fa; }
    .container { max-width: 600px; }
    .card { border: none; }
  </style>
</head>
<body>
<div class="container">
  <div class="card shadow-sm rounded-3">
    <div class="card-body p-4 p-md-5">
      <h1 class="card-title text-center mb-4">
        <c:choose>
          <c:when test="${models.formAction == 'add'}">
            Añadir Nuevo Usuario
          </c:when>
          <c:otherwise>
            Editar Usuario
          </c:otherwise>
        </c:choose>
      </h1>

      <%-- La acción del formulario apunta a la ruta 'save' del controlador --%>

      <form action="${pageContext.request.contextPath}/mvc/usuarios/save" method="post">

        <div class="mb-3">
          <label for="nombre" class="form-label">Nombre:</label>
          <input type="text" class="form-control rounded-pill" id="nombre" name="nombre"
                 value="<c:out value='${models.usuario.nombre}'/>" required>
        </div>

        <div class="mb-3">
          <label for="email" class="form-label">Email:</label>
          <input type="email" class="form-control rounded-pill" id="email" name="email"
                 value="<c:out value='${models.usuario.email}'/>" required>
        </div>

        <div class="d-grid gap-2 d-md-flex justify-content-md-end mt-4">
          <button type="submit" class="btn btn-primary rounded-pill px-4">Guardar</button>
          <a href="${pageContext.request.contextPath}/mvc/usuarios"
             class="btn btn-outline-secondary rounded-pill px-4">Cancelar</a>
        </div>
      </form>
    </div>
  </div>
  <footer class="text-center mt-4 text-muted">
    <p>&copy; Mi Aplicación CRUD con MVC</p>
  </footer>
</div>

<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz"
        crossorigin="anonymous"></script>
</body>
</html>
