package crm.models;

import jakarta.persistence.*;
import jakarta.validation.constraints.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;



@Entity
@Table(name = "client")
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class Client {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, updatable = false)
    private Long id;

    @Column(name = "name", length = 100, nullable = false)
    @NotBlank(message = "El nombre no puede estar vacío")
    @Size(min = 3, max = 100, message = "El nombre debe tener entre 3 y 100 caracteres")
    private String name;

    @Column(name = "email", length = 100, unique = true)
    @NotBlank(message = "El email no puede estar vacío")
    @Email(message = "El email debe ser válido")
    private String email;

    @Column(name = "phone", length = 20)
    @NotBlank(message = "El teléfono no puede estar vacío")
    @Pattern(regexp = "^\\+?[0-9\\- ]{7,20}$", message = "El teléfono debe ser válido (ej: +123456789)")
    private String phone;

    public Client(String name, String email, String phone) {
        this.name = name;
        this.email = email;
        this.phone = phone;
    }

    public Client(Client other) {
        this.id = other.id;
        this.name = other.name;
        this.email = other.email;
        this.phone = other.phone;
        // Copia otros atributos si los hubiera
    }
}