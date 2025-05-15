package auth;

import jakarta.enterprise.context.SessionScoped;
import jakarta.faces.context.FacesContext;
import jakarta.inject.Named;

import java.io.IOException;
import java.io.Serializable;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;

@Named("authBean")
@SessionScoped
public class AuthBean implements Serializable {

    private final String clientId = "NlKV0BQOclOFFbVVdDm48HBaZ1rmFcnY";
    private final String domain = "dev-lf4tj6jd1iuw1zqt.us.auth0.com";
    private final String clientSecret = "7BOA_4onCsCkWCV6KgB3GO4cjbr_sEkKDgaaqlk6WA1j6fLqSP5SCgoMY3IlYaHY";
    private final String redirectUri = "http://localhost:8080/ejemplo2/callback";
    private final String logoutRedirectUri = "http://localhost:8080/ejemplo2";

    private String userName;
    private String email;
    private String pictureUrl;
    private String nickname;


    public String login() {
        String url = String.format(
                "https://%s/authorize?response_type=code&client_id=%s&redirect_uri=%s&scope=openid profile email",
                domain,
                clientId,
                URLEncoder.encode(redirectUri, StandardCharsets.UTF_8)
        );

        try {
            FacesContext.getCurrentInstance().getExternalContext().redirect(url);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    public void verificarSesion() {
        if (userName == null || userName.isEmpty()) {
            try {
                FacesContext.getCurrentInstance().getExternalContext()
                        .redirect("index.xhtml");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }


    public String logout() {
        String url = String.format(
                "https://%s/v2/logout?client_id=%s&returnTo=%s",
                domain,
                clientId,
                URLEncoder.encode(logoutRedirectUri, StandardCharsets.UTF_8)
        );

        try {
            FacesContext.getCurrentInstance().getExternalContext().redirect(url);
        } catch (IOException e) {
            e.printStackTrace();
        }

        userName = null; // eliminar sesión local
        return null; // no navegación JSF
    }


    public String getUserName() {
        return userName;
    }

    public void setUserName(String name) {
        this.userName = name;
    }

    public boolean isLoggedIn() {
        return userName != null;
    }
    public String getClientId() {
        return clientId;
    }

    public String getClientSecret() {
        return clientSecret;
    }

    public String getDomain() {
        return domain;
    }

    public String getRedirectUri() {
        return redirectUri;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPictureUrl() {
        return pictureUrl;
    }

    public void setPictureUrl(String pictureUrl) {
        this.pictureUrl = pictureUrl;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }
}
