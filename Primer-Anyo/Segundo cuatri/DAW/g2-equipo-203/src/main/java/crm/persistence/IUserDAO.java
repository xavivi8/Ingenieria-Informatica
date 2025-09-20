package crm.persistence;

import crm.models.User;

import java.util.List;

public interface IUserDAO {
    void createUser(User user);

    User getUserById(Long id);

    User getUserByEmail(String email);

    List<User> getAllUsers();

    void updateUser(User user);

    void deleteUser(Long id);

    boolean login(String email, String password);
}
