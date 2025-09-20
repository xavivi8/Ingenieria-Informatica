package ujaen.daw.springmvcproject.controller;

import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller; // <-- en lugar de @Component
import org.springframework.ui.ModelMap;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import org.springframework.ui.Model;
import ujaen.daw.springmvcproject.dto.UserDTO;
import ujaen.daw.springmvcproject.models.User;
import ujaen.daw.springmvcproject.service.IUserService;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;
import java.util.logging.Logger;

@Controller
@RequestMapping("/users")
public class UserController {

    @Autowired
    private IUserService userService;

    @ModelAttribute
    public void configView(ModelMap model) {
        model.addAttribute("srvUrl", "/users");
        model.addAttribute("imgUrl", "/images");
    }

    private static final Logger logger = Logger.getLogger(UserController.class.getName());

    @GetMapping(path = {"","/home"})
    public String listarUsuarios(Model model) {
        List<UserDTO> lista = userService.findAll();
        model.addAttribute("usuarios", lista);
        logger.info("Listando usuarios");
        return "users/home";
    }

    // Metodo para mostrar el formulario de creación
    @GetMapping("/add")
    public String addForm(Model model) {
        model.addAttribute("user", new User());
        return "users/add";
    }

    // Metodo para procesar el formulario de creación
    @PostMapping("/add")
    public String add(@ModelAttribute("user") @Valid User user, BindingResult result, Model model) {
        String view = "redirect:/users/home"; // Redirección por defecto

        if (!result.hasErrors()) {
            userService.save(user);
            model.asMap().clear(); // Limpiar el modelo para evitar reenvíos
        } else {
            // Si hay errores, mantenemos el formulario
            model.addAttribute("user", user);
            view = "users/add";
        }
        return view;
    }

    @GetMapping("/delete")
    public String delete(@RequestParam(value="id",defaultValue="0")Long id, ModelMap model) {
        if (id != 0) {
            userService.deleteById(id);
            logger.info("Usuario con id " + id + " eliminado");
        }
        model.clear();
        return "redirect:/users/home";  // Redirige a la lista de usuarios después de eliminar
    }

    @GetMapping("/edit")
    public String editForm(@RequestParam(value="id",defaultValue="0")Long id, ModelMap model ) {
        model.addAttribute("user", userService.findById(id));
        return "users/edit";
    }

    @PostMapping("/edit")
    public String edit(@ModelAttribute("user") @Valid User user, BindingResult result, ModelMap model) {
        String view = "redirect:/users/home";
        if (!result.hasErrors()) {
            userService.save(user);
            model.clear(); // Asegúrate de que este view sea correcto
        } else {
            view="users/edit";  // En caso de error, el formulario sigue en la vista de edición
        }
        return view;
    }
}
