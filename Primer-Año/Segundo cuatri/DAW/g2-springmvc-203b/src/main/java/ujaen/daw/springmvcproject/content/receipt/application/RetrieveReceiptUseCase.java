package ujaen.daw.springmvcproject.content.receipt.application;

import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;

import java.util.List;

public interface RetrieveReceiptUseCase {

    Receipt findByIdReceipt(Integer idReceipt);
    List<Receipt> findAllReceipts();
}
