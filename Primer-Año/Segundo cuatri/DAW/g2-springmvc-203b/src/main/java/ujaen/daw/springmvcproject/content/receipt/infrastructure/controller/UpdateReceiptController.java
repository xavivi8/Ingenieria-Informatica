package ujaen.daw.springmvcproject.content.receipt.infrastructure.controller;

import jakarta.validation.Valid;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import ujaen.daw.springmvcproject.content.receipt.application.UpdateReceiptUseCase;
import ujaen.daw.springmvcproject.content.receipt.application.mapper.ReceiptEntityMapper;
import ujaen.daw.springmvcproject.content.receipt.infrastructure.controller.dto.input.ReceiptUpdateInputDto;

import java.util.logging.Logger;

@Controller
@RequestMapping("/receipts")
@RequiredArgsConstructor
public class UpdateReceiptController {

    private static final Logger logger = Logger.getLogger(UpdateReceiptController.class.getName());
    private final UpdateReceiptUseCase updateReceiptUseCase;


    @PostMapping("/edit")
    public String editReceiptPost(
            @ModelAttribute("cliente") @Valid ReceiptUpdateInputDto receiptUpdateInputDto
            , BindingResult result
            ,ModelMap model
    ) {
        String view="redirect:read/";
        if (!result.hasErrors()) {
            updateReceiptUseCase.updateReceipt(
                    ReceiptEntityMapper.INSTANCE
                            .toEntity(receiptUpdateInputDto)
            );
            model.clear();
            view=view+receiptUpdateInputDto.getId();
        } else {
            view="receipts/edit";
        }
        return view;
    }
}