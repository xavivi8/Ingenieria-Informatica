package ujaen.daw.springmvcproject.dto;

import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import ujaen.daw.springmvcproject.models.Product;

@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class ProductDTO {

    private Long id;

    @NotBlank(message = "La descripción no puede estar vacía")
    private String description;

    @NotBlank(message = "El nombre es obligatorio")
    @Size(max = 100, message = "El nombre no debe exceder 100 caracteres")
    private String name;

    @Min(value = 0, message = "El precio base no puede ser negativo")
    private double base_price;

    @Min(value = 0, message = "El stock no puede ser negativo")
    private int stock;

    // Constructor que permite crear un ProductDTO desde un Product
    public ProductDTO(Product product) {
        if (product != null) {
            this.id = product.getId();
            this.description = product.getDescription();
            this.name = product.getName();
            this.base_price = product.getBase_price();
            this.stock = product.getStock();
        }
    }
}

