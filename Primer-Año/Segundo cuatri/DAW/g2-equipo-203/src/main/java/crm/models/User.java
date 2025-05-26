package crm.models;

import crm.enums.UserRole;
import jakarta.persistence.*;
import jakarta.validation.Valid;
import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Pattern;
import jakarta.validation.constraints.Size;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "user_crm")
@Valid
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class User {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, updatable = false)
    private Long id;

    @Pattern(regexp = "\\d{8}-?[a-zA-Z]", message = "DNI no válido (debe tener 8 dígitos seguidos de una letra)")
    @Column(name = "dni", nullable = false)
    private String dni;

    @Email(message = "Correo electrónico no válido")
    @Column(name = "email", nullable = false)
    private String email;

    @Column(name = "password", nullable = false)
    @Size(min = 4, message = "La contraseña debe tener al menos 6 caracteres")
    private String password;

    @Column(name = "name", nullable = false)
    @NotBlank(message = "El nombre no puede estar vacío")
    private String name;

    @Column(name = "surname", nullable = false)
    @NotBlank(message = "El apellido no puede estar vacío")
    private String surname;

    @Column(name = "phone")
    @Pattern(regexp = "\\d{9}", message = "Teléfono no válido (debe contener 9 dígitos)")
    private String phone;

    @Column(name = "photo")
    private String photo;

    @Enumerated(EnumType.STRING)
    @Column(name = "role", nullable = false)
    private UserRole role;

    public User(Long id, String name) {
        this.id = id;
        this.name = name;
    }

    public User(Long id, String email, String password, String name, String dni, UserRole role) {
        this.id = id;
        this.email = email;
        this.password = password;
        this.name = name;
        this.dni = dni;
        this.role = role;
    }

    public User(String email, String password, String name, String dni, UserRole role) {
        this.email = email;
        this.password = password;
        this.name = name;
        this.dni = dni;
        this.role = role;
    }

    public User(User other) {

        this.id = other.id;
        this.dni = other.dni;
        this.email = other.email;
        this.password = other.password;
        this.name = other.name;
        this.surname = other.surname;
        this.phone = other.phone;
        this.photo = other.photo;
        this.role = other.role;

    }

    public String getPassword2() {
        return password;
    }
}
