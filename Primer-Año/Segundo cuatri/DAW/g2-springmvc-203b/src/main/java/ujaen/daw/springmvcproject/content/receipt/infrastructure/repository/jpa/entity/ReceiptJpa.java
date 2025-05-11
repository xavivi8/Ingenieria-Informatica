package ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.jpa.entity;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.time.LocalDate;

@Entity
@Table(name = "receipt")
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class ReceiptJpa {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, updatable = false)
    private Integer id;

    @Column(name = "date", nullable = false)
    private LocalDate date;

    @Column(name = "user_crm", nullable = false)
    private String userCrm;

    @Column(name = "amount", nullable = false)
    private double amount;

    public ReceiptJpa(LocalDate date, String userCrm, double amount) {
        this.date = date;
        this.userCrm = userCrm;
        this.amount = amount;
    }
}