package ujaen.daw.springmvcproject.content.receipt.infrastructure.controller.dto.output;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class ReceiptOutputDto {

    private double totalPrice;
    private String userCrm;
    private String client;
    private String receiptDetails;
}
