package ujaen.daw.springmvcproject.content.receipt.application;

import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;

public interface CreateReceiptUseCase {

    Integer saveReceipt(Receipt receipt);
}
