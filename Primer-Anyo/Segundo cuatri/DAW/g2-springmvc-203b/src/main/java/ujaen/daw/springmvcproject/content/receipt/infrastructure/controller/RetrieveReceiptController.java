package ujaen.daw.springmvcproject.content.receipt.infrastructure.controller;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import ujaen.daw.springmvcproject.content.receipt.application.RetrieveReceiptUseCase;
import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;

import java.util.logging.Logger;

@Controller
@RequestMapping("/receipts")
@RequiredArgsConstructor
public class RetrieveReceiptController {

    private static final Logger logger = Logger.getLogger(RetrieveReceiptController.class.getName());
    private final RetrieveReceiptUseCase retrieveReceiptUseCase;


    // ############################### DEFAULT ROUTE ###############################
    @GetMapping(path = {"","/home"})
    public String homeReceipt(
            ModelMap model
    ) {
        model.addAttribute("receipts", retrieveReceiptUseCase.findAllReceipts());
        logger.info("Listando facturas");
        return "receipt/home";
    }

    @GetMapping("/read")
    public String readReceipt(
            @RequestParam(value="id",defaultValue="0") Integer id
            , ModelMap model
    ) {

        model.addAttribute("receipts", new Receipt());
        return "receipt/create";
    }

    @GetMapping("/read/{id}")
    public String readReceiptById(
            @PathVariable Integer id
            ,ModelMap model
    ) {

        model.addAttribute("receipts", new Receipt());
        return "receipt/create";
    }

    @GetMapping("/edit")
    public String showReceiptsToEdit(
            @RequestParam(value="id",defaultValue="0") Integer id
            ,ModelMap model
    ) {

        model.addAttribute("receipt", retrieveReceiptUseCase.findByIdReceipt(id));
        return "receipts/edit";
    }
}
