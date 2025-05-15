package daw.app.usuario;

import daw.app.AppConfig;
import daw.app.UsuarioAuthService;
import daw.app.dao.ItemDAO;
import daw.app.dao.MensajeDAO;
import daw.app.dao.UsuarioDAO;
import daw.app.item.Item;
import daw.app.mensaje.Mensaje;
import daw.app.qualifiers.DAOJpa;
import jakarta.annotation.PostConstruct;
import jakarta.faces.context.ExternalContext;
import jakarta.faces.context.FacesContext;
import jakarta.faces.view.ViewScoped;
import jakarta.inject.Inject;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.inject.Named;
import jakarta.servlet.ServletException;
import jakarta.validation.Valid;
import java.io.Serializable;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.Objects;
import java.io.*;
import java.util.Base64;
import jakarta.servlet.http.Part;
import org.json.JSONObject;

@Named("usuarioCtrl")
@ViewScoped
public class UsuarioController implements Serializable {
    @Inject
    private transient HttpServletRequest request;

    @Inject @DAOJpa
    private UsuarioDAO usuarioDAO;

    @Inject @DAOJpa
    private MensajeDAO mensajeDAO;

    @Inject @DAOJpa
    private ItemDAO itemDAO;

    @Inject
    private UsuarioAuthService authService;

    @Inject
    private AppConfig app;

    @Inject
    private daw.app.BlacklistService blacklist;


    @Valid
    private Usuario usuarioVista = new Usuario();

    @Valid
    private Usuario usuario = new Usuario();

    private String nuevaContrasena;
    private String confirmacionContrasena;
    private String email;
    private String contrasena;
    private String mensajeError;
    private boolean mostrarVentana = false;
    private Part archivoFoto;

    private String terminoBusqueda = "";
    private boolean realizandoBusqueda = false;
    private List<Usuario> usuariosFiltrados;
    private boolean sinResultados = false;
    private Usuario usuarioAEliminar = new Usuario();

    public Usuario getUsuarioAEliminar() { return usuarioAEliminar; }

    public List<Usuario> getUsuariosFiltrados() {
        return usuariosFiltrados;
    }

    public void setUsuariosFiltrados(List<Usuario> usuariosFiltrados) {
        this.usuariosFiltrados = usuariosFiltrados;
    }

    public boolean isSinResultados() {
        return sinResultados;
    }
    public void setSinResultados(boolean sinResultados) {
        this.sinResultados = sinResultados;
    }

    public String getTerminoBusqueda() {return terminoBusqueda;}
    public void setTerminoBusqueda(String terminoBusqueda) {this.terminoBusqueda = terminoBusqueda;}

    public boolean isRealizandoBusqueda() {return realizandoBusqueda;}
    public void setRealizandoBusqueda(boolean realizandoBusqueda) {this.realizandoBusqueda = realizandoBusqueda;}

    public Part getArchivoFoto() {return archivoFoto;}
    public void setArchivoFoto(Part archivoFoto) {this.archivoFoto = archivoFoto;}

    public boolean isMostrarVentana() { return mostrarVentana; }
    public void setMostrarVentana(boolean mostrarVentana) { this.mostrarVentana = mostrarVentana; }

    public String getNuevaContrasena() {return nuevaContrasena;}
    public void setNuevaContrasena(String nuevaContrasena) {this.nuevaContrasena = nuevaContrasena;}

    public Usuario getUsuario() { return usuario; }
    public void setUsuario(Usuario usuario) { this.usuario = usuario; }

    public String getConfirmacionContrasena() { return confirmacionContrasena; }
    public void setConfirmacionContrasena(String confirmacionContrasena) { this.confirmacionContrasena = confirmacionContrasena; }

    public String getEmail() { return email; }
    public void setEmail(String email) { this.email = email; }

    public String getContrasena() { return contrasena; }
    public void setContrasena(String contrasena) { this.contrasena = contrasena; }

    public String getMensajeError() { return mensajeError; }

    public Usuario getUsuarioVista() {
        return usuarioVista;
    }
    public void setUsuarioVista(Usuario usuarioVista) {
        this.usuarioVista = usuarioVista;
    }

    public String registrarUsuario() {
        if (!usuario.getContrasenia().equals(confirmacionContrasena)) {
            mensajeError = "Las contraseñas no coinciden";
            return null;
        }

        if (usuarioDAO.existeEmail(usuario.getEmail())) {
            mensajeError = "Ya existe un usuario registrado con ese email.";
            return null;
        }

        if (usuarioDAO.existeTelefono(usuario.getTelefono())) {
            mensajeError = "Ya existe un usuario registrado con ese teléfono.";
            return null;
        }

        if (blacklist.estaEnEmail(usuario.getEmail())) {
            mensajeError = "Este email no está disponible.";
            return null;
        }

        if (blacklist.estaEnTelefono(usuario.getTelefono())) {
            mensajeError = "Este teléfono no está disponible.";
            return null;
        }


        usuario.setRol("USUARIOS");
        usuario.setContrasenia(authService.encryptPassword(usuario.getContrasenia()));
        usuario.setFotoPerfilBase64(app.getImagenPorDefecto());
        usuarioDAO.crea(usuario);
        usuario = new Usuario();
        mensajeError = "";
        confirmacionContrasena = "";

        return "/usuario/iniciar_sesion?faces-redirect=true";
    }

    public String updateusuario() {
        usuarioDAO.guarda(usuarioVista);
        request.getSession().setAttribute("usuarioVista", usuarioVista);

        return "/item/perfil?faces-redirect=true";
    }

    public String cambContrasenia() {
        boolean esUsuarioNuevoOIDC = authService.verifyPassword("temporal", usuarioVista.getContrasenia());
        if (!esUsuarioNuevoOIDC && !authService.verifyPassword(contrasena, usuarioVista.getContrasenia())) {
            mensajeError = "Contraseña actual incorrecta";
            return null;
        }

        if(!Objects.equals(nuevaContrasena, confirmacionContrasena)){
            mensajeError = "No coincide la nueva contraseña";
            return null;
        }

       // usuarioVista.setContrasenia(nuevaContrasena);
        usuarioVista.setContrasenia(authService.encryptPassword(nuevaContrasena));

        usuarioDAO.guarda(usuarioVista);
        request.getSession().setAttribute("usuarioVista", usuarioVista);

        if (esUsuarioNuevoOIDC) {
            usuarioVista.setContrasenia(authService.encryptPassword(nuevaContrasena));
            usuarioDAO.guarda(usuarioVista);
            request.getSession().setAttribute("usuarioVista", usuarioVista);
            return "/usuario/home.xhtml?faces-redirect=true";
        }
        return "/item/perfil?faces-redirect=true";
    }

    public String recuperarContrasenia() {
        Usuario usuario = usuarioDAO.buscaPorEmail(email);

        if (usuario == null) {
            mensajeError = "No existe ningún usuario con ese email.";
            mostrarVentana = false;
            return null;
        }

        nuevaContrasena = generarContraseniaAleatoria(8);
        usuario.setContrasenia(authService.encryptPassword(nuevaContrasena));


        usuarioDAO.guarda(usuario);
        request.getSession().setAttribute("usuarioVista", usuarioVista);

        mostrarVentana = true;
        return null;
    }

    private String generarContraseniaAleatoria(int longitud) {
        String caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < longitud; i++) {
            int index = (int) (Math.random() * caracteres.length());
            sb.append(caracteres.charAt(index));
        }
        return sb.toString();
    }

    public String redirigirLogin() {
        mostrarVentana = false;
        email="";
        return "/usuario/iniciar_sesion?faces-redirect=true";
    }

    public String subirFoto() {
        if (archivoFoto == null || archivoFoto.getSize() == 0 || usuarioVista == null) {
            mensajeError = "No se ha seleccionado ninguna imagen";
            return null;
        }

        String tipo = archivoFoto.getContentType();
        if (!tipo.equals("image/png") && !tipo.equals("image/jpeg")) {
            mensajeError = "Solo se permiten imágenes PNG o JPEG";
            return null;
        }

        try (InputStream input = archivoFoto.getInputStream()) {
            byte[] bytes = input.readAllBytes();
            String base64 = Base64.getEncoder().encodeToString(bytes);
            String dataUrl = "data:" + tipo + ";base64," + base64;

            usuarioVista.setFotoPerfilBase64(dataUrl);
            usuarioDAO.guarda(usuarioVista);
            request.getSession().setAttribute("usuarioVista", usuarioVista);

            return "/item/perfil?faces-redirect=true";

        } catch (IOException e) {
            mensajeError = "Error al procesar la imagen";
            e.printStackTrace();
            return null;
        }
    }

    public void reestrablceMssg(){
        mensajeError="";
    }

    public String cerrarSesion() throws ServletException, IOException {
        String idToken = (String) request.getSession().getAttribute("idToken");
        request.logout();
        request.getSession().invalidate();
        usuarioVista = new Usuario();
        usuario = new Usuario();
        mensajeError = "";
        confirmacionContrasena="";
        contrasena="";
        email="";
        mostrarVentana = false;
        archivoFoto = null;
        ExternalContext ec = FacesContext.getCurrentInstance().getExternalContext();
        String postLogoutRedirectUri = "http://localhost:8080/app/index.xhtml";
        try {
            ec.redirect("http://localhost:9090/realms/ProyectoOpenID/protocol/openid-connect/logout" +
                    "?id_token_hint=" + idToken +
                    "&post_logout_redirect_uri=" + postLogoutRedirectUri);
        } catch (java.io.UnsupportedEncodingException e) {
            // Manejar la excepción, por ejemplo, loguearla o lanzar una RuntimeException
            e.printStackTrace();
        }
        return null; ///"/index?faces-redirect=true";
    }

    public void cargarUsuarioAutenticado() {
        try {
            String emailAutenticado = request.getRemoteUser();
            if (emailAutenticado != null && !emailAutenticado.isBlank()) {
                Usuario u = usuarioDAO.buscaPorEmail(emailAutenticado);
                if (u != null) {
                    usuarioVista = u;
                    request.getSession().setAttribute("usuarioVista", usuarioVista);
                    return;
                }
            }
        } catch (Exception e) {
            mensajeError = "Error cargando los datos del usuario";
            e.printStackTrace();
        }

        // Si no está logueado o no se encuentra el usuario, modo público
        usuarioVista = new Usuario();
    }

    public void cargarUsuarioPorEmail() {
        String correo = request.getParameter("email");

        if (correo != null) {
            usuario = usuarioDAO.buscaPorEmail(correo);
            if (usuario == null) {
                mensajeError = "No se encontró el usuario con ese email.";
            }
        }
    }

    public String buscarUsuarios() {
        realizandoBusqueda = true;
        request.getSession().setAttribute("terminoBusqueda", terminoBusqueda);

        return "/usuario/home?faces-redirect=true";
    }

    public List<Usuario> getUsuariosNomDesc(boolean publico) {
        String termino = terminoBusqueda != null ? terminoBusqueda.trim() : "";

        if (realizandoBusqueda && !termino.isEmpty()) {
            realizandoBusqueda = false;
            request.getSession().removeAttribute("terminoBusqueda");
            usuariosFiltrados=(!publico)?usuarioDAO.buscarPorNombreODescripcion(termino, usuarioVista.getId()):usuarioDAO.buscarPorNombreODescripcion(termino,null);
            sinResultados = usuariosFiltrados.isEmpty();
        } else {
            realizandoBusqueda = false;
            request.getSession().removeAttribute("terminoBusqueda");
            terminoBusqueda = "";
            usuariosFiltrados=(!publico)?usuarioDAO.usuariosMenosTu(usuarioVista.getId()):usuarioDAO.usuariosMenosAdmin();
            sinResultados = false;
        }

        return usuariosFiltrados;
    }

    public boolean esEmpresa(int idUsuario) {
        Usuario u = usuarioDAO.buscaId(idUsuario);
        return u != null && u.isEmpresa();
    }

    @PostConstruct
    public void init() {
        if (usuarioVista == null || usuarioVista.getId() == null) {
            cargarUsuarioAutenticado();
        }

        Object terminoGuardado = request.getSession().getAttribute("terminoBusqueda");
        if (terminoGuardado != null) {
            terminoBusqueda = terminoGuardado.toString();
            realizandoBusqueda = true;
        }

        Object userGuardado = request.getSession().getAttribute("usuarioVista");
        if (userGuardado != null && userGuardado instanceof Usuario) {
            usuarioVista = (Usuario) userGuardado;
        }

    }

    public void cargarUsuarioParaEliminar() {
        try {
            String idParam = request.getParameter("id");
            if (idParam != null) {
                Integer id = Integer.parseInt(idParam);
                usuarioAEliminar = usuarioDAO.buscaId(id);
            }
        } catch (Exception e) {
            mensajeError = "Error cargando el usuario para eliminar";
            e.printStackTrace();
        }
    }

    public String confirmarEliminacionUsuario() {
        if (usuarioAEliminar != null && usuarioAEliminar.getId() != null) {

            blacklist.agregar(usuarioAEliminar.getEmail(), usuarioAEliminar.getTelefono());

            List<Mensaje> mensajesBorrados=mensajeDAO.obtenerMensajesDeUsuario(usuarioAEliminar.getId());
            for (Mensaje m : mensajesBorrados) {
                mensajeDAO.borra(m.getId());
            }

            List<Item> itemsBorrados=itemDAO.itemsUsuario(usuarioAEliminar.getId());
            for (Item i : itemsBorrados) {
                itemDAO.borra(i.getId());
            }


            usuarioDAO.borra(usuarioAEliminar.getId());
        }
        return "/usuario/home?faces-redirect=true";
    }

    public String getRutaLogo(boolean publico) {
        return (publico) ? "/index" : "/usuario/home";
    }

    public String redirigirAOIDC() {
        ExternalContext ec = FacesContext.getCurrentInstance().getExternalContext();
        try {
            ec.redirect("http://localhost:9090/realms/ProyectoOpenID/protocol/openid-connect/auth?" +
                    "client_id=frontend-jsf" +
                    "&response_type=code" +
                    "&scope=openid" +
                    "&redirect_uri=http://localhost:8080/app/usuario/inicio_openid.xhtml");
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public String procesarInicioSesionOpenId() {
        try {
            String code = request.getParameter("code");
            if (code == null || code.isBlank()) {
                mensajeError = "No se recibió el código de autenticación";
                return "/index.xhtml?faces-redirect=true";
            }
            // Intercambio del código por un token de acceso
            String[] datos = obtenerEmailYTokenDesdeCode(code);
            // Extracción del email del token para procesarlo
            String emailOpenId = datos[0];
            String idToken = datos[1];
            request.getSession().setAttribute("idToken", idToken);

            Usuario u = usuarioDAO.buscaPorEmail(emailOpenId);

            if (u == null) {
                Usuario nuevo = new Usuario();
                nuevo.setEmail(emailOpenId);
                nuevo.setNombreUsuario(emailOpenId.split("@")[0]);
                nuevo.setNombreCompleto("temporal");
                nuevo.setContrasenia(authService.encryptPassword("temporal"));
                nuevo.setFotoPerfilBase64(app.getImagenPorDefecto());
                nuevo.setRol("USUARIOS");
                nuevo.setDireccion("Dirección de ejemplo");
                nuevo.setTelefono("000000000");
                nuevo.setEmpresa(false);
                usuarioDAO.crea(nuevo);
                this.usuarioVista = nuevo;
                request.getSession().setAttribute("usuarioVista", usuarioVista);

                return "/usuario/establecer_contrasenia.xhtml?faces-redirect=true";
            } else {
                this.usuarioVista = u;
                request.getSession().setAttribute("usuarioVista", usuarioVista);
                return "/usuario/home.xhtml?faces-redirect=true";
            }
        } catch (Exception e) {
            mensajeError = "Error procesando inicio de sesión con OpenID";
            e.printStackTrace();
            return "/index.xhtml?faces-redirect=true";
        }
    }

    private String[] obtenerEmailYTokenDesdeCode(String code) throws IOException {
        String tokenEndpoint = "http://localhost:9090/realms/TuNombreDeReino/protocol/openid-connect/token";
        String clientId = "TuClientID";
        String clientSecret = "TuClientSecret";
        String redirectUri = "http://localhost:8080/app/usuario/inicio_openid.xhtml";

        URL url = new URL(tokenEndpoint);
        HttpURLConnection con = (HttpURLConnection) url.openConnection();
        con.setRequestMethod("POST");
        con.setDoOutput(true);
        con.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");

        String postData = "grant_type=authorization_code"
                + "&code=" + URLEncoder.encode(code, StandardCharsets.UTF_8)
                + "&client_id=" + URLEncoder.encode(clientId, StandardCharsets.UTF_8)
                + "&client_secret=" + URLEncoder.encode(clientSecret, StandardCharsets.UTF_8)
                + "&redirect_uri=" + URLEncoder.encode(redirectUri, StandardCharsets.UTF_8);

        try (OutputStream os = con.getOutputStream()) {
            byte[] input = postData.getBytes(StandardCharsets.UTF_8);
            os.write(input, 0, input.length);
        }

        int status = con.getResponseCode();
        if (status != 200) {
            throw new IOException("Error al obtener el token. Código HTTP: " + status);
        }

        InputStream responseStream = con.getInputStream();
        String json = new String(responseStream.readAllBytes(), StandardCharsets.UTF_8);

        JSONObject obj = new JSONObject(json);
        String accessToken = obj.getString("access_token");
        String idToken = obj.getString("id_token");

        String[] partes = accessToken.split("\\.");
        String payload = new String(Base64.getUrlDecoder().decode(partes[1]), StandardCharsets.UTF_8);
        JSONObject payloadJson = new JSONObject(payload);

        String email = payloadJson.optString("email", payloadJson.getString("preferred_username"));

        return new String[]{email, idToken};
    }





}





