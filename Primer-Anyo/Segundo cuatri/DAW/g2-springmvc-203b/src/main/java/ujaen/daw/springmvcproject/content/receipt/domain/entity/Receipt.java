package ujaen.daw.springmvcproject.content.receipt.domain.entity;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.time.LocalDate;


@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class Receipt {

    private Integer id;
    private LocalDate date;
    private String userCrm;
    private double amount;

    public Receipt(LocalDate date, String userCrm, double amount) {
        this.date = date;
        this.userCrm = userCrm;
        this.amount = amount;
    }
}