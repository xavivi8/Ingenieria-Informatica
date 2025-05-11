package ujaen.daw.springmvcproject.service;

import ujaen.daw.springmvcproject.dto.UserDTO;
import ujaen.daw.springmvcproject.models.User;

import java.util.List;

public interface IUserService {

    List<UserDTO> findAll();

    UserDTO findById(Long id);

    User save(User user);

    void deleteById(Long id);
}
