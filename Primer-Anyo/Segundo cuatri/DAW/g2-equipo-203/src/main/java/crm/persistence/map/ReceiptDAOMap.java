package crm.persistence.map;

import crm.models.Receipt;
import crm.persistence.ReceiptDAO;
import crm.qualifiers.DAOMap;
import jakarta.enterprise.context.Dependent;

import java.io.Serializable;
import java.time.LocalDate;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@DAOMap
@Dependent
public class ReceiptDAOMap implements ReceiptDAO, Serializable {

    private Map<Integer, Receipt> receipts;
    private  Integer idReceipt = 1;

    @Override
    public Receipt buscaByCampo(String campo) {
        return null; // TODO Criteria API
    }

    @Override
    public List<Receipt> readByClientId(Long clientId) {
        return List.of();
    }

    @Override
    public List<Receipt> searchByUserOrClient(Long idUserCrm, Long idClient) {
        return List.of();
    }

    @Override
    public List<Receipt> searchByMinPriceOrUser(Long idUserCrm, Double minTotalPrice) {
        return List.of();
    }

    @Override
    public Integer deleteByTotalPriceGreaterThan(double threshold) {
        return 0;
    }

    @Override
    public List<Receipt> filter(Long userId, Long clientId, Double minTotal, Double maxTotal, LocalDate startDate, LocalDate endDate) {
        return List.of();
    }

    @Override
    public Receipt create(Receipt r) {
        Receipt newRe=new Receipt(r);
        newRe.setId(idReceipt);
        receipts.put(idReceipt, newRe);
        r.setId(idReceipt);
        idReceipt++;
        return r;
    }

    @Override
    public Receipt readById(Integer id) {
        Receipt found = receipts.get(id);
        if (found != null) found=new Receipt(found);
        return found;
    }

    @Override
    public Receipt update(Receipt r) {
        return null; // TODO
    }

    @Override
    public boolean delete(Integer id) {
        boolean result=false;
        if (receipts.containsKey(id)) {
            receipts.remove(id);
            result = true;
        }
        return result;
    }

    @Override
    public List<Receipt> readAll() {
        return receipts.values().stream().collect(Collectors.toList());
    }

    @Override
    public boolean save(Receipt r) {
        boolean result=false;
        if (receipts.containsKey(r.getId())) {
            Receipt newRe=new Receipt(r);
            receipts.replace(r.getId(),newRe);
            result=true;
        }
        return result;
    }
}
