package crm.models.dto.input;

import jakarta.persistence.Column;
import jakarta.validation.Valid;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotNull;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Valid
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class ReceiptDetailsCreateInputDTO {

    @NotNull(message = "Debe seleccionar al menos un producto")
    @Column(name = "id_product", nullable = false)
    private Long idProduct;

    @NotNull(message = "Debe seleccionar que cantidad de producto quieres")
    @Min(value = 1, message = "Debes seleccionar al menos un producto")
    private Integer amount;
}
