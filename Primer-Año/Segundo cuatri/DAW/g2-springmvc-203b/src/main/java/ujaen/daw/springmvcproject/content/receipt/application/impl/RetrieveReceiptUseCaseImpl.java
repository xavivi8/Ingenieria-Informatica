package ujaen.daw.springmvcproject.content.receipt.application.impl;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import ujaen.daw.springmvcproject.content.receipt.application.RetrieveReceiptUseCase;
import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;
import ujaen.daw.springmvcproject.content.receipt.domain.repository.RetrieveReceiptRepository;

import java.util.List;

@Service
@RequiredArgsConstructor
public class RetrieveReceiptUseCaseImpl implements RetrieveReceiptUseCase {

    private final RetrieveReceiptRepository retrieveReceiptRepository;

    @Override
    public Receipt findByIdReceipt(Integer idReceipt) {
        return null;
    }

    @Override
    public List<Receipt> findAllReceipts() {
        return List.of();
    }
}