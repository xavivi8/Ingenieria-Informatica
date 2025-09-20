package ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.impl;

import jakarta.persistence.EntityNotFoundException;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Repository;
import ujaen.daw.springmvcproject.content.receipt.application.mapper.ReceiptEntityMapper;
import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;
import ujaen.daw.springmvcproject.content.receipt.domain.repository.RetrieveReceiptRepository;
import ujaen.daw.springmvcproject.content.receipt.infrastructure.repository.jpa.ReceiptRepositoryJpa;

import java.util.List;

@Repository
@RequiredArgsConstructor
public class RetrieveReceiptRepositoryImpl implements RetrieveReceiptRepository {

    private final ReceiptRepositoryJpa receiptRepositoryJpa;

    @Override
    public Receipt findByIdSubject(Integer idReceipt) {

        return ReceiptEntityMapper.INSTANCE.toEntity(
                receiptRepositoryJpa
                        .findById(idReceipt)
                        .orElseThrow( () -> new EntityNotFoundException("Receipt not found") )
        );
    }

    @Override
    public List<Receipt> findAllReceipts() {

        return ReceiptEntityMapper.INSTANCE
                .toEntityList(
                        receiptRepositoryJpa.findAll()
                );
    }
}