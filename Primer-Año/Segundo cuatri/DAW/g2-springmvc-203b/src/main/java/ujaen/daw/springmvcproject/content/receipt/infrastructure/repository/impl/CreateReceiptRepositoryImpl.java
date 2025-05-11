package ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.impl;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Repository;
import ujaen.daw.springmvcproject.content.receipt.application.mapper.ReceiptEntityMapper;
import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;
import ujaen.daw.springmvcproject.content.receipt.domain.repository.CreateReceiptRepository;
import ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.jpa.ReceiptRepositoryJpa;

@Repository
@RequiredArgsConstructor
public class CreateReceiptRepositoryImpl implements CreateReceiptRepository {

    private final ReceiptRepositoryJpa receiptRepositoryJpa;


    @Override
    public Integer saveReceipt(Receipt receipt) {

        return receiptRepositoryJpa.save(
                        ReceiptEntityMapper.INSTANCE.toEntityJpa(
                                receipt
                        )
                )
                .getId();
    }
}