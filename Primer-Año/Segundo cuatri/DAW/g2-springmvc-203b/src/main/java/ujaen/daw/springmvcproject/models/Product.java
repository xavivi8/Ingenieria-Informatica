package ujaen.daw.springmvcproject.models;

import jakarta.persistence.*;
import jakarta.validation.Valid;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.io.Serializable;

@Entity
@Table(name = "product")
@Valid
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class Product implements Serializable {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, updatable = false)
    private Long id;

    @Column(name = "description", nullable = false)
    @NotBlank(message = "La descripción no puede estar vacía")
    private String description;

    @Column(name = "name", nullable = false)
    @NotBlank(message = "El nombre es obligatorio")
    @Size(max = 100, message = "El nombre no debe exceder 100 caracteres")
    private String name;

    @Column(name = "base_price", nullable = false)
    private double base_price;

    @Column(name = "stock", nullable = false)
    @Min(value = 0, message = "El stock no puede ser negativo")
    private int stock;

//    @OneToMany(mappedBy = "product")
//    private List<ReceiptDetails> receiptDetails;

    public Product(String name, String description, double base_price, int stock) {
        this.name = name;
        this.description = description;
        this.base_price = base_price;
        this.stock = stock;
    }

    public Product(String name, double base_price, int stock) {
        this.name = name;
        this.base_price = base_price;
        this.stock = stock;
    }

    public Product(Product other) {
        if(other != null) {
            this.id = other.id;
            this.description = other.description;
            this.name = other.name;
            this.base_price = other.base_price;
            this.stock = other.stock;
        }
    }
}
