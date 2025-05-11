package ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.impl;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Repository;
import ujaen.daw.springmvcproject.content.receipt.application.mapper.ReceiptEntityMapper;
import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;
import ujaen.daw.springmvcproject.content.receipt.domain.repository.UpdateReceiptRepository;
import ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.jpa.ReceiptRepositoryJpa;

@Repository
@RequiredArgsConstructor
public class UpdateReceiptRepositoryImpl implements UpdateReceiptRepository {

    private final ReceiptRepositoryJpa receiptRepositoryJpa;

    @Override
    public Receipt updateReceipt(Receipt receipt) {
        return ReceiptEntityMapper.INSTANCE
                .toEntity(
                        receiptRepositoryJpa
                                .save(
                                        ReceiptEntityMapper.INSTANCE
                                                .toEntityJpa(receipt)
                                )
                );
    }
}