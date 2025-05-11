package org.example.trabajo_dirigido.web; // O el paquete que estés usando para controladores

import jakarta.inject.Inject;
import jakarta.mvc.Controller;
import jakarta.mvc.Models;
import jakarta.mvc.View;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.ws.rs.*;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;
import org.example.trabajo_dirigido.dao.UsuarioDAOMap;
import org.example.trabajo_dirigido.model.Usuario;

import java.net.URI;
import java.util.List;
import java.util.Optional;

@Controller
@Path("usuarios")
public class UsuarioController {

    @Inject
    private UsuarioDAOMap usuarioDAO;

    @Inject
    private Models models;

    @Inject
    private HttpServletRequest request;

    @GET
    @View("listaUsuarios.jsp")
    public void listUsuarios() {
        List<Usuario> listaUsuarios = usuarioDAO.findAll();
        models.put("listaUsuarios", listaUsuarios);

        String successMessage = request.getParameter("success");
        if (successMessage != null) models.put("successMessage", successMessage);
        String errorMessage = request.getParameter("error");
        if (errorMessage != null) models.put("errorMessage", errorMessage);
    }

    /**
     * Muestra el formulario para añadir un nuevo usuario.
     * CAMBIO: Usar @View y void para que MVC renderice la vista directamente.
     */
    @GET
    @Path("add")
    @View("formularioUsuario.jsp") // El path es relativo a src/main/webapp/
    public void showNewForm() {
        models.put("usuario", new Usuario()); // Usuario vacío para el formulario
        models.put("formAction", "add");    // Indica a la vista que es una acción de añadir
    }

    /**
     * Muestra el formulario para editar un usuario existente o redirige si no se encuentra.
     * Este método es más complejo porque puede renderizar una vista o redirigir.
     */
    @GET
    @Path("edit/{id}")
    public Response showEditForm(@PathParam("id") Long id) {
        Optional<Usuario> usuarioOpt = usuarioDAO.findById(id);
        if (usuarioOpt.isPresent()) {
            models.put("usuario", usuarioOpt.get());
            models.put("formAction", "edit");

            return Response.ok("formularioUsuario.jsp").build();
        } else {
            return Response.seeOther(URI.create(request.getContextPath() + "/mvc/usuarios?error=UsuarioNoEncontrado")).build();
        }
    }


    @POST
    @Path("save")
    @Consumes(MediaType.APPLICATION_FORM_URLENCODED)
    public Response saveUsuario(@BeanParam UsuarioForm form) {

        if (form == null) {
            return Response.seeOther(URI.create(request.getContextPath()
                    + "/mvc/usuarios?error=ErrorFormulario")).build();
        }

        Usuario user = new Usuario();

        String successMsgKey;
        if (form.getId() != null && form.getId() != 0) {
            successMsgKey = "UsuarioActualizado";
        } else {
            successMsgKey = "UsuarioCreado";
        }

        user.setNombre(form.getNombre());
        user.setEmail(form.getEmail());
        usuarioDAO.save(user);

        return Response.seeOther(URI.create(request.getContextPath()
                + "/mvc/usuarios?success=" + successMsgKey)).build();
    }

    @POST
    @Path("delete/{id}")
    public Response deleteUsuario(@PathParam("id") Long id) {
        boolean deleted = usuarioDAO.deleteById(id);
        String msgKey = deleted ? "UsuarioEliminado" : "ErrorAlEliminar";
        String param = deleted ? "success" : "error";
        return Response.seeOther(URI.create(request.getContextPath() + "/mvc/usuarios?" + param + "=" + msgKey)).build();
    }
}