package crm.models;

import jakarta.security.enterprise.CallerPrincipal;

public class AppPrincipal extends CallerPrincipal {
    private final User user;

    public AppPrincipal(User user) {
        super(user.getEmail());
        this.user = user;
    }
    public User getUser() {
        return user;
    }
}
