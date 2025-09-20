package ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.impl;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Repository;
import ujaen.daw.springmvcproject.content.receipt.domain.repository.DeleteReceiptRepository;
import ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.jpa.ReceiptRepositoryJpa;

@Repository
@RequiredArgsConstructor
public class DeleteReceiptRepositoryImpl implements DeleteReceiptRepository {

    private final ReceiptRepositoryJpa receiptRepositoryJpa;


    @Override
    public Boolean deleteByIdReceipt(Integer idReceipt) {

        receiptRepositoryJpa.deleteById(idReceipt);
        return true;
    }
}