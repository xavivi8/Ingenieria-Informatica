package crm.models;

import jakarta.persistence.*;
import jakarta.validation.Valid;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotNull;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Entity
@Table(name = "receipt_details")
@Valid
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class ReceiptDetails {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, updatable = false)
    private Integer id;

    @NotNull(message = "Debe seleccionar al menos un producto")
    @Column(name = "id_product", nullable = false)
    private Long idProduct;

    @NotNull(message = "Debe seleccionar que cantidad de producto quieres")
    @Min(value = 1, message = "Debes seleccionar al menos un producto")
    @Column(name = "amount", nullable = false)
    private Integer amount;

    public ReceiptDetails(
            Long idProduct
            ,Integer amount
    ) {
        this.setIdProduct(idProduct);
        this.setAmount(amount);
    }
}