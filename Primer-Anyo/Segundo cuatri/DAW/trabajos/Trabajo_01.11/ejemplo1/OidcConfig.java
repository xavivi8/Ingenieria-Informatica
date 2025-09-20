package daw.app;

import jakarta.enterprise.context.ApplicationScoped;
import jakarta.inject.Named;
import jakarta.security.enterprise.authentication.mechanism.http.OpenIdAuthenticationMechanismDefinition;
import java.io.IOException;
import java.util.Properties;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
@OpenIdAuthenticationMechanismDefinition(
        providerURI = "${oidcConfig.issuerUri}",
        clientId = "${oidcConfig.clientId}",
        clientSecret = "${oidcConfig.clientSecret}",
        redirectURI = "${baseURL}/usuario/inicio_openid.xhtml",
        redirectToOriginalResource = false,
        jwksReadTimeout = 5000
)
*/

@ApplicationScoped
@Named("oidcConfig")
public class OidcConfig {

    private static final Logger LOGGER = Logger.getLogger(OidcConfig.class.getName());

    private String issuerUri;
    private String clientId;
    private String clientSecret;

    public String getIssuerUri() { return issuerUri; }
    public String getClientId() { return clientId; }
    public String getClientSecret() { return clientSecret; }

    public OidcConfig() {
        try {
            var props = new Properties();
            props.load(getClass().getResourceAsStream("/oidc.properties"));
            this.issuerUri = props.getProperty("issuerUri");
            this.clientId = props.getProperty("clientId");
            this.clientSecret = props.getProperty("clientSecret");
        } catch (IOException e) {
            LOGGER.log(Level.SEVERE, "No se pudo cargar oidc.properties", e);
        }
    }
}
