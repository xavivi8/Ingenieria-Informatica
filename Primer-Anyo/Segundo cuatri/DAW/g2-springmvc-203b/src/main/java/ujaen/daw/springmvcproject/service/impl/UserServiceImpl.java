package ujaen.daw.springmvcproject.service.impl;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ujaen.daw.springmvcproject.dto.UserDTO;
import ujaen.daw.springmvcproject.models.User;
import ujaen.daw.springmvcproject.persistence.IUserDAO;
import ujaen.daw.springmvcproject.service.IUserService;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@Service
public class UserServiceImpl implements IUserService {

    @Autowired
    private IUserDAO userDAO;

    @Override
    public List<UserDTO> findAll() {
        List<User> users = userDAO.findAll();

        // Mapeamos cada User a UserDTO usando un stream
        List<UserDTO> userDTOs = users.stream().map(user -> {
            return new UserDTO(
                    user.getId(),
                    user.getDni(),
                    user.getEmail(),
                    user.getPassword(),
                    user.getName(),
                    user.getSurname(),
                    user.getPhone(),
                    user.getPhoto(),
                    user.getRole()
            );
        }).collect(Collectors.toList());

        return userDTOs;
    }

    @Override
    public UserDTO findById(Long id) {
        Optional<User> optionalUser = userDAO.findById(id);

        return optionalUser.map(user -> new UserDTO(
                user.getId(),
                user.getDni(),
                user.getEmail(),
                user.getPassword(),
                user.getName(),
                user.getSurname(),
                user.getPhone(),
                user.getPhoto(),
                user.getRole()
        )).orElse(null);
    }

    @Override
    public User save(User user) {
        return userDAO.save(user);
    }

    @Override
    public void deleteById(Long id) {
        userDAO.deleteById(id);
    }
}