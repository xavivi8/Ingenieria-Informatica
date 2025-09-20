package ujaen.daw.springmvcproject.content.receipt.infrastructure.controller;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import ujaen.daw.springmvcproject.content.receipt.application.CreateReceiptUseCase;
import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;

import java.util.logging.Logger;

@Controller
@RequestMapping("/receipts")
@RequiredArgsConstructor
public class CreateReceiptController {

    private final CreateReceiptUseCase createReceiptUseCase;
    private static final Logger logger = Logger.getLogger(CreateReceiptController.class.getName());


    @GetMapping("/create")
    public String createReceiptForm(
            ModelMap model
    ) {

        model.addAttribute("receipts", new Receipt());
        return "receipt/create";
    }

}
