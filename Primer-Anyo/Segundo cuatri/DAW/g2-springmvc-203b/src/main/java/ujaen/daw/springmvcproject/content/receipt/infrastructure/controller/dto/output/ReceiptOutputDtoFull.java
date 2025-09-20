package ujaen.daw.springmvcproject.content.receipt.infrastructure.controller.dto.output;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.time.LocalDate;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class ReceiptOutputDtoFull {

    private Integer id;
    private LocalDate date;
    private double totalPrice;
    private String userCrm;
    private String client;
    private String receiptDetails;
}
