package crm.models;

import jakarta.persistence.*;
import jakarta.validation.Valid;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.PastOrPresent;
import jakarta.validation.constraints.PositiveOrZero;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.io.Serializable;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "receipt")
@Valid
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class Receipt implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "id", nullable = false, updatable = false)
    private Integer id;

    @NotNull(message = "La fecha no puede ser nula")
    @PastOrPresent(message = "La fecha debe ser pasada o presente")
    @Column(name = "date", nullable = false)
    private LocalDate date;

    @PositiveOrZero(message = "El precio total debe ser mayor o igual a 0")
    @Column(name = "total_price", nullable = false)
    private double totalPrice;

    @NotNull(message = "El usuario no puede estar vacío")
    @Column(name = "id_user_crm", nullable = false)
    private Long idUserCrm;

    @NotNull(message = "El cliente no puede estar vacío")
    @Column(name = "id_client", nullable = false)
    private Long idClient;

    @OneToMany(
            cascade = CascadeType.ALL,
            orphanRemoval = true,
            fetch = FetchType.EAGER
    )
    @JoinColumn(
            name = "id_receipt",
            referencedColumnName = "id"
    )
    private List<ReceiptDetails> details = new ArrayList<>();

    public Receipt(
            Long idUserCrm,
            Long idClient,
            List<ReceiptDetails> details
    ) {
        this.setIdUserCrm(idUserCrm);
        this.setIdClient(idClient);
        this.setDetails(details);
    }

    public Receipt(
            Integer id,
            LocalDate date,
            double totalPrice,
            Long idUserCrm,
            Long idClient
    ) {
        this.setId(id);
        this.setDate(date);
        this.setTotalPrice(totalPrice);
        this.setIdUserCrm(idUserCrm);
        this.setIdClient(idClient);
        this.details = new ArrayList<>();
    }

    // Copy constructor
    public Receipt(Receipt r) {
        this.setId(r.getId());
        this.setDate(r.getDate());
        this.setTotalPrice(r.getTotalPrice());
        this.setIdUserCrm(r.getIdUserCrm());
        this.setIdClient(r.getIdClient());
    }
}