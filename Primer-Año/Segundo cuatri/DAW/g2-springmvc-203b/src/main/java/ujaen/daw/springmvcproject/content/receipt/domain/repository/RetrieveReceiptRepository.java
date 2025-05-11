package ujaen.daw.springmvcproject.content.receipt.domain.repository;

import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;

import java.util.List;

public interface RetrieveReceiptRepository {

    Receipt findByIdSubject(Integer idReceipt);
    List<Receipt> findAllReceipts();
}
