package ujaen.daw.springmvcproject.content.receipt.application.impl;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import ujaen.daw.springmvcproject.content.receipt.application.UpdateReceiptUseCase;
import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;
import ujaen.daw.springmvcproject.content.receipt.domain.repository.UpdateReceiptRepository;

@Service
@RequiredArgsConstructor
public class UpdateReceiptUseCaseImpl implements UpdateReceiptUseCase {

    private final UpdateReceiptRepository updateReceiptRepository;

    @Override
    public Receipt updateReceipt(Receipt receipt) {

        return updateReceiptRepository.updateReceipt(receipt);
    }
}