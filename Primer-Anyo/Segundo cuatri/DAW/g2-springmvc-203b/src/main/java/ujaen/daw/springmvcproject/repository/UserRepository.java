package ujaen.daw.springmvcproject.repository;

import org.springframework.data.repository.CrudRepository;
import ujaen.daw.springmvcproject.models.User;

public interface UserRepository extends CrudRepository<User, Long> {
}
