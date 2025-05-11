package ujaen.daw.springmvcproject.content.receipt.application.impl;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import ujaen.daw.springmvcproject.content.receipt.application.DeleteReceiptUseCase;
import ujaen.daw.springmvcproject.content.receipt.domain.repository.DeleteReceiptRepository;

@Service
@RequiredArgsConstructor
public class DeleteReceiptUseCaseImpl implements DeleteReceiptUseCase {

    private final DeleteReceiptRepository deleteReceiptRepository;

    @Override
    public Boolean deleteByIdReceipt(Integer idReceipt) {

        return deleteReceiptRepository.deleteByIdReceipt(idReceipt);
    }
}
