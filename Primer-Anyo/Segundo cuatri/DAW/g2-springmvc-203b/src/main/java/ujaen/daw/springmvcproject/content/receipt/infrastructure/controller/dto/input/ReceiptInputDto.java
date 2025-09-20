package ujaen.daw.springmvcproject.content.receipt.infrastructure.controller.dto.input;

import jakarta.validation.Valid;
import jakarta.validation.constraints.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.time.LocalDate;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@Valid
public class ReceiptInputDto {

    @NotNull(message = "La fecha no puede ser nula")
    @PastOrPresent(message = "La fecha debe ser pasada o presente")
    private LocalDate date;

    @PositiveOrZero(message = "El precio total debe ser mayor o igual a 0")
    private double amount;

    @NotBlank(message = "El usuario no puede estar vacío")
    @Size(min = 3, max = 50, message = "El usuario debe tener entre 3 y 50 caracteres")
    @Pattern(regexp = "^[a-zA-Z0-9\\s]+$", message = "El usuario solo puede contener letras, números y espacios")
    private String userCrm;
}
