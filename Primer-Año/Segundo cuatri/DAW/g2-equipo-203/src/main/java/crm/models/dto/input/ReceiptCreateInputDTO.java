package crm.models.dto.input;

import jakarta.validation.Valid;
import jakarta.validation.constraints.NotNull;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.List;

@Valid
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class ReceiptCreateInputDTO {

    @NotNull(message = "El usuario no puede estar vacío")
    private Long idUserCrm;

    @NotNull(message = "El cliente no puede estar vacío")
    private Long idClient;

    private List<ReceiptDetailsCreateInputDTO> details;
}
