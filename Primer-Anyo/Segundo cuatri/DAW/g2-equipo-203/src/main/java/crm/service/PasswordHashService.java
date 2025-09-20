package crm.service;

import jakarta.annotation.PostConstruct;
import jakarta.enterprise.context.ApplicationScoped;
import jakarta.inject.Inject;
import jakarta.security.enterprise.identitystore.Pbkdf2PasswordHash;

import java.util.HashMap;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

@ApplicationScoped
public class PasswordHashService {

    private static final Logger logger = Logger.getLogger(PasswordHashService.class.getName());

    //Encryption algorithm
    @Inject
    private Pbkdf2PasswordHash passwordHash;

    @PostConstruct
    public void init() {
        //Configure encryption algorithm
        Map<String, String> parameters = new HashMap<>();
        parameters.put("Pbkdf2PasswordHash.Iterations", "3072");
        parameters.put("Pbkdf2PasswordHash.Algorithm", "PBKDF2WithHmacSHA512");
        parameters.put("Pbkdf2PasswordHash.SaltSizeBytes", "64");
        passwordHash.initialize(parameters);
    }

    public boolean verifyPassword(String password, String hashedPassword) {
        try {
            return passwordHash.verify(password.toCharArray(), hashedPassword);
        } catch (Exception e) {
            logger.log(Level.SEVERE, "Error al verificar la contraseña: ", e);
            return false;
        }
    }

    public String encryptPassword(String password) {
        try {
            String encryptedPass = passwordHash.generate(password.toCharArray());
            logger.log(Level.INFO, "Clave cifrada: {0}", encryptedPass);
            return encryptedPass;
        } catch (Exception e) {
            logger.log(Level.SEVERE, "Error al cifrar la contraseña: ", e);
            return null;
        }
    }
}
