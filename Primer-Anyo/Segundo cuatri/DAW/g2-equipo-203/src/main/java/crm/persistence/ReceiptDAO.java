package crm.persistence;

import crm.models.Receipt;

import java.time.LocalDate;
import java.util.List;

public interface ReceiptDAO extends GenericDAO<Receipt,Integer>{
    //Declare here specific methods for EntityDAO
    public Receipt buscaByCampo(String campo);

    // Criteria API
    List<Receipt> readByClientId(Long clientId);
    List<Receipt> searchByUserOrClient(Long idUserCrm, Long idClient);
    List<Receipt> searchByMinPriceOrUser(Long idUserCrm, Double minTotalPrice);
    Integer deleteByTotalPriceGreaterThan(double threshold);
    List<Receipt> filter(Long      userId,
                         Long      clientId,
                         Double    minTotal,
                         Double    maxTotal,
                         LocalDate startDate,
                         LocalDate endDate);
}
