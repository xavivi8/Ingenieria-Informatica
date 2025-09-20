package crm.persistence;

import crm.models.ReceiptDetails;

import java.util.List;

public interface ReceiptDetailsDAO extends GenericDAO<ReceiptDetails,Integer>{
    ReceiptDetails buscaByCampo(String campo);
    List<ReceiptDetails> findByIdReceipt(Integer idReceipt);
}
