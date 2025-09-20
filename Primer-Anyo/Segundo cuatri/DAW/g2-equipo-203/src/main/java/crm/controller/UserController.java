package crm.controller;

import crm.AppConfig;
import crm.models.User;
import crm.persistence.IUserDAO;
import crm.qualifiers.DAOJpa;
import crm.qualifiers.DAOMap;
import jakarta.annotation.PostConstruct;
import jakarta.faces.application.FacesMessage;
import jakarta.faces.context.FacesContext;
import jakarta.faces.view.ViewScoped;
import jakarta.inject.Inject;
import jakarta.inject.Named;
import jakarta.security.enterprise.SecurityContext;
import lombok.Getter;
import lombok.Setter;

import java.io.Serial;
import java.io.Serializable;
import java.security.Principal;
import java.util.List;
import java.util.Objects;
import java.util.logging.Logger;

@Named(value = "userCtrl")
@ViewScoped
@Getter
@Setter
public class UserController implements Serializable {

    @Serial
    private static final long serialVersionUID = 1L;

    private final Logger logger = Logger.getLogger(UserController.class.getName());

    //@Inject @DAOMap
    @Inject @DAOJpa
    private IUserDAO userDao;

    @Inject
    private FacesContext fc;

    @Inject
    private SecurityContext sc;

    @Inject
    private AppConfig appConfig;

    private Principal principal;
    private User user;
    private User usuarioAEliminar;
    private User usuarioOriginal;
    private boolean cambiosDetectados;
    private String resumenCambios;

    @PostConstruct
    public void init() {
        user = new User();

        String currentUser = "Anónimo";
        principal = sc.getCallerPrincipal();

        if (principal != null) {
            currentUser = principal.getName();
        }

        logger.info("Petición de usuario: " + currentUser);

        // Crear usuarios iniciales si no existen
        List<User> existentes = userDao.getAllUsers();
    }

    public List<User> getUsers() {
        return userDao.getAllUsers();
    }

    public void recuperar() {
        user = userDao.getUserById(user.getId());
        if (user == null) {
            fc.addMessage(null, new FacesMessage("El usuario indicado no existe"));
        }
        usuarioOriginal = new User();
        usuarioOriginal.setId(user.getId());
        usuarioOriginal.setName(user.getName());
        usuarioOriginal.setSurname(user.getSurname());
        usuarioOriginal.setEmail(user.getEmail());
        usuarioOriginal.setPhone(user.getPhone());
        usuarioOriginal.setRole(user.getRole());
    }
    public User findUserById(Long id) {
        return userDao.getUserById(id);
    }

    public String crea() {
        userDao.createUser(user);
        return "/users/home.xhtml?faces-redirect=true";
    }

    public String guarda() {
        userDao.updateUser(user);
        return "home?faces-redirect=true&id=" + user.getId();
    }

    public void prepararEliminacion(User user) {
        this.usuarioAEliminar = user;
    }

    public void confirmarEliminacion() {
        if (usuarioAEliminar != null) {
            userDao.deleteUser(usuarioAEliminar.getId());
            FacesContext.getCurrentInstance().addMessage(null,
                    new FacesMessage("Usuario eliminado correctamente"));
            usuarioAEliminar = null;
        }
    }

    public String borra() {
        userDao.deleteUser(user.getId());
        fc.addMessage(null, new FacesMessage("Usuario borrado correctamente"));
        return "listado";
    }

    public String borra(User u) {
        userDao.deleteUser(u.getId());
        fc.addMessage(null, new FacesMessage("Usuario borrado correctamente"));
        return "listado";
    }

    public String cargarParaEdicion(User user) {
        this.user = user;
        return "edit";
    }

    public void recupera() {
        user = userDao.getUserById(user.getId());
        if (user == null) {
            fc.addMessage(null, new FacesMessage("El cliente indicado no existe"));
        }
    }

    public String cancelarEdicion() {
        return "/users/home.xhtml?faces-redirect=true";
    }

    public String analizarCambios() {
        StringBuilder sb = new StringBuilder();
        cambiosDetectados = false;

        if (!Objects.equals(usuarioOriginal.getName(), user.getName())) {
            cambiosDetectados = true;
            sb.append("Nombre: ").append(usuarioOriginal.getName()).append(" → ").append(user.getName()).append("\n");
        }

        if (!Objects.equals(usuarioOriginal.getSurname(), user.getSurname())) {
            cambiosDetectados = true;
            sb.append("Apellidos: ").append(usuarioOriginal.getSurname()).append(" → ").append(user.getSurname()).append("\n");
        }

        if (!Objects.equals(usuarioOriginal.getEmail(), user.getEmail())) {
            cambiosDetectados = true;
            sb.append("Email: ").append(usuarioOriginal.getEmail()).append(" → ").append(user.getEmail()).append("\n");
        }

        if (!Objects.equals(usuarioOriginal.getPhone(), user.getPhone())) {
            cambiosDetectados = true;
            sb.append("Teléfono: ").append(usuarioOriginal.getPhone()).append(" → ").append(user.getPhone()).append("\n");
        }

        if (!Objects.equals(usuarioOriginal.getRole(), user.getRole())) {
            cambiosDetectados = true;
            sb.append("Rol: ").append(usuarioOriginal.getRole()).append(" → ").append(user.getRole()).append("\n");
        }

        resumenCambios = sb.toString();
        return cambiosDetectados ? null : cancelarEdicion();
    }

    public String guardarCambios() {
        userDao.updateUser(user);
        return "/users/home.xhtml?faces-redirect=true";
    }

    public void editRow(User u) {
        this.user = u;
    }

    public void cancelEditRow() {
        this.user = new User();
    }

    public void actualizaUsuario() {
        userDao.updateUser(user);
        cancelEditRow();
    }

    public User findUserByEmail(String email) {
        return userDao.getUserByEmail(email);
    }

    public void actualizarFoto(User user) {
        if (user.getPhoto() == null || user.getPhoto().isBlank()) {
            user.setPhoto("/resources/img/poro.png");
        }
        userDao.updateUser(user);
        FacesContext.getCurrentInstance().addMessage(null,
                new FacesMessage(FacesMessage.SEVERITY_INFO, "Imagen actualizada", ""));
    }

}
