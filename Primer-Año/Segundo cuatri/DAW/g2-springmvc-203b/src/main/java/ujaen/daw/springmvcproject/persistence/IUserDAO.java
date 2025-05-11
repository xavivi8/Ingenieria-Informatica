package ujaen.daw.springmvcproject.persistence;

import ujaen.daw.springmvcproject.models.User;

import java.util.List;
import java.util.Optional;

public interface IUserDAO {

    List<User> findAll();

    Optional<User> findById(Long id);

    User save(User user);

    void deleteById(Long id);
}
