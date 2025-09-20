package daw.app.controller;

import daw.app.AppConfig;
import daw.app.model.Libro;
import daw.app.model.Usuario;
import daw.app.model.dao.DAOJpa;
import daw.app.model.dao.ILibrosDAO;
import daw.app.model.dao.IUsuarioDAO;
import jakarta.annotation.PostConstruct;
import jakarta.faces.application.FacesMessage;
import jakarta.faces.context.FacesContext;
import jakarta.faces.view.ViewScoped;
import jakarta.inject.Inject;
import jakarta.inject.Named;
import jakarta.security.enterprise.SecurityContext;

import java.io.Serial;
import java.io.Serializable;
import java.security.Principal;
import java.util.List;
import java.util.stream.Collectors;

@Named("ctrlLibros")
@ViewScoped
public class LibroController implements Serializable {

    @Serial
    private static final long serialVersionUID = 1L;

    @Inject
    private daw.app.service.NotificacionService notificacionService;


    // DAO de libros y usuarios
    @Inject @DAOJpa
    private ILibrosDAO libroDAO;
    @Inject @DAOJpa
    private IUsuarioDAO usuarioDAO;

    @Inject
    private FacesContext fc;
    @Inject
    private SecurityContext sc;
    @Inject
    private AppConfig appConfig;

    // Para recuperación del principal (si se usa)
    private Principal principal;

    // View-model: libro en edición/creación y filtro de búsqueda
    private Libro libro;
    private String filtro;

    public LibroController() { }

    @PostConstruct
    public void init() {
        libro = new Libro();
        principal = null;
    }

    /**
     * Devuelve la lista de libros, filtrada por título o autor si filtro no está vacío.
     */
    public List<Libro> getLibros() {
        List<Libro> todos = libroDAO.buscaTodos();
        if (filtro == null || filtro.trim().isEmpty()) {
            return todos;
        }
        String f = filtro.trim().toLowerCase();
        return todos.stream()
                .filter(l -> l.getTitulo().toLowerCase().contains(f)
                        || l.getAutor().toLowerCase().contains(f))
                .collect(Collectors.toList());
    }

    public Libro getLibro() {
        return libro;
    }

    public String getFiltro() {
        return filtro;
    }

    public void setFiltro(String filtro) {
        this.filtro = filtro;
    }

    /**
     * Recupera un libro por parámetro id.
     */
    public void recupera() {
        libro = libroDAO.buscaId(libro.getId());
        if (libro == null) {
            fc.addMessage(null, new FacesMessage("El libro indicado no existe"));
        }
    }

    /**
     * Crea un libro asignándole el usuario actual.
     */
    public String crea() {
        Principal p = sc.getCallerPrincipal();
        if (p != null) {
            Usuario u = usuarioDAO.buscarPorNombreUsuario(p.getName());
            libro.setUsuario(u);
            libroDAO.crea(libro);

            // Enviar notificación
            String mensaje = "El usuario " + u.getNombreUsuario() + " ha registrado el libro \"" + libro.getTitulo() + "\".";
            notificacionService.enviarMensaje(mensaje, u.getNombreUsuario());


            return "visualizaLibro?faces-redirect=true&id=" + libro.getId();
        }

        fc.addMessage(null, new FacesMessage("No se pudo crear el libro: usuario no autenticado"));
        return null;
    }


    /**
     * Elimina el libro y refresca la tabla via AJAX.
     */
    public void borra(Libro libro) {
        if (libro == null || libro.getId() <= 0) {
            mostrarMensajeError("Error: Libro no válido.");
            return;
        }
        libroDAO.borra(libro.getId());
        mostrarMensajeInfo("Libro eliminado con éxito.");

        // Forzar refresco de la tabla y mensaje
        FacesContext ctx = FacesContext.getCurrentInstance();
        ctx.getPartialViewContext().getRenderIds().add("formLibros:tablaLibros");
        ctx.getPartialViewContext().getRenderIds().add("formLibros:mensajeNoLibros");
    }

    /**
     * Prepara la edición en línea.
     */
    public void editRow(Libro libro) {
        this.libro = libro;
    }

    public void cancelEditRow() {
        this.libro = new Libro();
    }

    /**
     * Guarda los cambios de un libro editado.
     */
    public String actualizaLibro() {
        libroDAO.guarda(libro);
        return "listadoLibros?faces-redirect=true";
    }

    private void mostrarMensajeInfo(String mensaje) {
        FacesContext.getCurrentInstance()
                .addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, mensaje, null));
    }

    private void mostrarMensajeError(String mensaje) {
        FacesContext.getCurrentInstance()
                .addMessage(null, new FacesMessage(FacesMessage.SEVERITY_ERROR, mensaje, null));
    }

    public void resetFiltro() {
        this.filtro = null;
    }

    public Usuario getUsuarioActual() {
        Principal p =  sc.getCallerPrincipal();
        if (p != null) {
            Usuario u = usuarioDAO.buscarPorNombreUsuario(p.getName());
            return u;
        }
        return null;
    }

}
