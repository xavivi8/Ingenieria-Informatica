package ujaen.daw.springmvcproject.content.receipt.application.impl;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import ujaen.daw.springmvcproject.content.receipt.application.CreateReceiptUseCase;
import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;
import ujaen.daw.springmvcproject.content.receipt.domain.repository.CreateReceiptRepository;

@Service
@RequiredArgsConstructor
public class CreateReceiptUseCaseImpl implements CreateReceiptUseCase {

    private CreateReceiptRepository createReceiptRepository;

    @Override
    public Integer saveReceipt(Receipt receipt) {

        return createReceiptRepository.saveReceipt(receipt);
    }

}
