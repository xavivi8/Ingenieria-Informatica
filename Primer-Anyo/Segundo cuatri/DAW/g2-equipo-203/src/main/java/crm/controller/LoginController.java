package crm.controller;

import crm.models.User;
import jakarta.enterprise.context.SessionScoped;
import jakarta.faces.application.FacesMessage;
import jakarta.faces.context.ExternalContext;
import jakarta.faces.context.FacesContext;
import jakarta.faces.view.ViewScoped;
import jakarta.inject.Inject;
import jakarta.inject.Named;
import jakarta.security.enterprise.AuthenticationStatus;
import jakarta.security.enterprise.SecurityContext;
import jakarta.security.enterprise.authentication.mechanism.http.AuthenticationParameters;
import jakarta.security.enterprise.credential.UsernamePasswordCredential;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotEmpty;
import lombok.Getter;
import lombok.Setter;
import lombok.extern.java.Log;

import java.io.Serializable;


@Named
@SessionScoped
@Getter
@Setter
@Log
public class LoginController implements Serializable {

    @NotEmpty(message = "El correo es obligatorio")
    @Email(message = "Formato de correo inválido")
    private String email;

    @NotEmpty(message = "La contraseña es obligatoria")
    private String password;

    private boolean emailVerificado = false;

    @Inject
    private FacesContext facesContext;

    @Inject
    private ExternalContext externalContext;

    @Inject
    private SecurityContext securityContext;  // Inyectado correctamente

    @Inject
    private HttpServletRequest request;

    @Inject
    private UserController userCtrl;

    private User usuarioActual;

    public String goToStep2() {
        // Solo validamos que el email exista (sin contraseña)
        boolean emailExiste = true; // Aquí implementa la validación de existencia del correo

        if (!emailExiste) {
            facesContext.addMessage("", new FacesMessage(FacesMessage.SEVERITY_ERROR,
                    "Correo no registrado", ""));
            email = null;
            return "loginStep1.xhtml";
        }

        emailVerificado = true;
        return "loginStep2.xhtml";
    }

    public String login() {
        if (!emailVerificado) {
            facesContext.addMessage("", new FacesMessage(FacesMessage.SEVERITY_ERROR,
                    "Debe verificar el correo antes", ""));
            return "loginStep1.xhtml";
        }

        // Autenticación programática del contenedor
        AuthenticationParameters authParams = AuthenticationParameters.withParams()
                .credential(new UsernamePasswordCredential(email, password))
                .newAuthentication(true);

        HttpServletResponse response = (HttpServletResponse) externalContext.getResponse();
        AuthenticationStatus status = securityContext.authenticate(request, response, authParams);

        if (status == AuthenticationStatus.SUCCESS) {
            log.info("Usuario autenticado exitosamente: " + email);
            usuarioActual = userCtrl.findUserByEmail(email);
            return "/users/home?faces-redirect=true";
        }

        log.warning("Fallo en la autenticación del contenedor");
        facesContext.addMessage("", new FacesMessage(FacesMessage.SEVERITY_WARN,
                "Error de autenticación", ""));
        email = null;
        password = null;
        emailVerificado = false;
        return "loginStep1.xhtml";
    }

    public boolean isLoggedIn() {
        return securityContext.getCallerPrincipal() != null;
    }

    public String logout() throws ServletException {
        request.logout();
        request.getSession().invalidate();
        return "/index.xhtml?faces-redirect=true";
    }
}
