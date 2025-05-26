package crm;

import crm.models.AppPrincipal;
import crm.models.User;
import crm.persistence.IUserDAO;
import crm.qualifiers.DAOJpa;
import crm.service.PasswordHashService;
import jakarta.enterprise.context.ApplicationScoped;
import jakarta.inject.Inject;
import jakarta.security.enterprise.credential.UsernamePasswordCredential;
import jakarta.security.enterprise.identitystore.CredentialValidationResult;
import jakarta.security.enterprise.identitystore.IdentityStore;

import java.util.HashSet;
import java.util.Set;
import java.util.logging.Logger;

import static jakarta.security.enterprise.identitystore.CredentialValidationResult.INVALID_RESULT;
import static java.util.Arrays.asList;

@ApplicationScoped
public class AppIdentityStore implements IdentityStore {

    private static final Logger logger = Logger.getLogger(AppIdentityStore.class.getName());

    @Inject
    private PasswordHashService passwordHashService;

    @Inject
    @DAOJpa
    private IUserDAO userDao;

    public AppIdentityStore() {
    }

    public CredentialValidationResult validate(UsernamePasswordCredential usernamePasswordCredential) {

        String username = usernamePasswordCredential.getCaller(); //email
        String password = usernamePasswordCredential.getPasswordAsString();
        boolean authenticated = false;

        User user = userDao.getUserByEmail(username);

        if (user != null && passwordHashService.verifyPassword(password, user.getPassword2())) {
            authenticated = true;
            logger.info(String.format("Authenticated user %s", username));
        } else {
            logger.warning(String.format("Authentication error for %s", username));
        }

        if (authenticated) {
            Set<String> roles = new HashSet<>(asList(user.getRole().toString()));

            return new CredentialValidationResult(new AppPrincipal(user), roles);
        }
        return INVALID_RESULT;
    }
}
