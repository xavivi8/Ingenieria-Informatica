package crm.servlets;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "FacturaServlet", urlPatterns = {"/FacturaServlet"})
public class FacturaServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Obtener parámetros del formulario
        String date = request.getParameter("date");
        String totalPrice = request.getParameter("totalPrice");
        String userId = request.getParameter("id_user");
        String clientId = request.getParameter("id_client");

        // Validación básica de datos
        if (totalPrice == null || totalPrice.trim().isEmpty()) {
            request.setAttribute("errorMessage", "El precio total es obligatorio.");
            request.getRequestDispatcher("/error.jsp").forward(request, response);
            return;
        }

        // TODO Procesar la lógica de negocio, guardar en DAOMAP.
        request.getRequestDispatcher("/success.jsp").forward(request, response); // TODO success.jsp
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Redirige las solicitudes GET al método POST o maneja según convenga.
        doPost(request, response);
    }
}

