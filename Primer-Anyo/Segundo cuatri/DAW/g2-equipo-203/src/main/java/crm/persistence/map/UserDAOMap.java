package crm.persistence.map;

import crm.models.User;
import crm.persistence.IUserDAO;
import crm.qualifiers.DAOMap;
import crm.service.PasswordHashService;
import jakarta.enterprise.context.ApplicationScoped;
import jakarta.inject.Inject;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@ApplicationScoped
@DAOMap
public class UserDAOMap implements IUserDAO, Serializable {

    @Inject
    private PasswordHashService passwordHashService;

    private final Map<Long, User> users;
    private Long currentId = 1L;

    public UserDAOMap() {
        users = new HashMap<>();
    }

    @Override
    public void createUser(User user) {
        String encryptedPassword = passwordHashService.encryptPassword(user.getPassword());
        User newUser = new User(user);
        newUser.setId(currentId);
        newUser.setPassword(encryptedPassword);
        users.put(currentId, newUser);
        user.setId(currentId);
        currentId++;
    }

    @Override
    public User getUserById(Long id) {
        User user = users.get(id);
        return user != null ? new User(user) : null;
    }

    @Override
    public List<User> getAllUsers() {
        return users.values().stream().map(User::new).collect(Collectors.toList());
    }

    @Override
    public void updateUser(User user) {
        if (users.containsKey(user.getId())) {
            User updated = new User(user);
            users.replace(user.getId(), updated);
        }
    }

    @Override
    public void deleteUser(Long id) {
        users.remove(id);
    }

    @Override
    public boolean login(String email, String password) {
        for (User u : users.values()) {
            if (u.getEmail().equalsIgnoreCase(email) && u.getPassword().equals(password)) {
                return true;
            }
        }
        return false;
    }

    public int userCount() {
        return users.size();
    }

    public User getUserByEmail(String email) {
        for (User u : users.values()) {
            if (u.getEmail().equalsIgnoreCase(email)) {
                return new User(u);
            }
        }
        return null;
    }
}