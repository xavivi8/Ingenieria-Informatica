package auth;

import com.auth0.jwt.JWT;
import com.auth0.jwt.interfaces.DecodedJWT;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import jakarta.inject.Inject;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.*;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;

@WebServlet("/callback")
public class CallbackServlet extends HttpServlet {

    @Inject
    private AuthBean authBean;

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {

        String code = req.getParameter("code");
        if (code == null) {
            resp.sendRedirect("index.xhtml");
            return;
        }

        // Preparar solicitud POST para intercambiar el código por un token
        URL url = new URL("https://" + authBean.getDomain() + "/oauth/token");
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("POST");
        conn.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
        conn.setDoOutput(true);

        String body = String.format(
                "grant_type=authorization_code&client_id=%s&client_secret=%s&code=%s&redirect_uri=%s",
                URLEncoder.encode(authBean.getClientId(), "UTF-8"),
                URLEncoder.encode(authBean.getClientSecret(), "UTF-8"),
                URLEncoder.encode(code, "UTF-8"),
                URLEncoder.encode(authBean.getRedirectUri(), "UTF-8")
        );

        try (OutputStream os = conn.getOutputStream()) {
            os.write(body.getBytes());
        }

        // Leer y parsear el JSON de respuesta
        InputStream is = conn.getInputStream();
        ObjectMapper mapper = new ObjectMapper();
        JsonNode json = mapper.readTree(is);

        // Extraer y decodificar el id_token
        String idToken = json.get("id_token").asText();
        DecodedJWT decoded = JWT.decode(idToken);

        String nombre = decoded.getClaim("name").asString();
        if (nombre == null || nombre.isEmpty()) {
            nombre = decoded.getSubject();
        }
        authBean.setEmail(decoded.getClaim("email").asString());
        authBean.setPictureUrl(decoded.getClaim("picture").asString());
        authBean.setNickname(decoded.getClaim("nickname").asString());


        authBean.setUserName(nombre);

        // Redirigir a la vista protegida
        resp.sendRedirect("home.xhtml");
    }
}
