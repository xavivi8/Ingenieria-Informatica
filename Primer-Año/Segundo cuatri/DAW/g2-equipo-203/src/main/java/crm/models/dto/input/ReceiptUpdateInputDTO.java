package crm.models.dto.input;

import jakarta.validation.Valid;
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
public class ReceiptUpdateInputDTO {

    @NotNull(message = "Debes elegir la factura que quieres actualizar")
    private Integer idReceipt;

    private Long idUserCrm;

    private Long idClient;
}
