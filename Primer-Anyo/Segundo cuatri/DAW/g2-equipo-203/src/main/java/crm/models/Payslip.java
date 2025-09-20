package crm.models;

import crm.enums.PayslipStatus;
import jakarta.persistence.*;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.PastOrPresent;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDate;

@Entity // (Nómina)
@Table(name = "payslip")
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class Payslip implements Serializable {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, updatable = false)
    private Long id;

    @Column(name = "userId", nullable = false, updatable = false)
    private long userID;

    @NotNull(message = "La fecha no puede ser nula")
    @PastOrPresent(message = "La fecha debe ser pasada o presente")
    @Column(name = "date", nullable = false)
    private LocalDate date;


    @Column(name = "base_salary", nullable = false)
    private Double baseSalary;

    @Enumerated(EnumType.STRING)
    @Column(name = "status", nullable = false)
    private PayslipStatus status;

    public Payslip(Payslip p) {
        this.id = p.getId();
        this.userID = p.getUserID();
        this.date = p.getDate();
        this.baseSalary = p.getBaseSalary();
        this.status = p.getStatus();
    }
}
