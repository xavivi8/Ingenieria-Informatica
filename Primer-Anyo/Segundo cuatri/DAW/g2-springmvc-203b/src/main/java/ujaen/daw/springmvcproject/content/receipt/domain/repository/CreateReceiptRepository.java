package ujaen.daw.springmvcproject.content.receipt.domain.repository;

import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;

public interface CreateReceiptRepository {

    Integer saveReceipt(Receipt receipt);
}
