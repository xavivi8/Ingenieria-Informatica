package ujaen.daw.springmvcproject.dto;

import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Pattern;
import jakarta.validation.constraints.Size;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import ujaen.daw.springmvcproject.enums.UserRole;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
public class UserDTO {

    private Long id;

    @Pattern(regexp = "\\d{8}-?[a-zA-Z]", message = "DNI no válido (debe tener 8 dígitos seguidos de una letra)")
    private String dni;

    @Email(message = "Correo electrónico no válido")
    private String email;

    @Size(min = 4, message = "La contraseña debe tener al menos 6 caracteres")
    private String password;

    @NotBlank(message = "El nombre no puede estar vacío")
    private String name;

    @NotBlank(message = "El apellido no puede estar vacío")
    private String surname;

    @Pattern(regexp = "\\d{9}", message = "Teléfono no válido (debe contener 9 dígitos)")
    private String phone;

    private String photo;

    private UserRole role;
}
