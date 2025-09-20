package ujaen.daw.springmvcproject.content.receipt.infrastructure.controller;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import ujaen.daw.springmvcproject.content.receipt.application.DeleteReceiptUseCase;

import java.util.logging.Logger;

@Controller
@RequestMapping("/receipts")
@RequiredArgsConstructor
public class DeleteReceiptController {

    private static final Logger logger = Logger.getLogger(DeleteReceiptController.class.getName());
    private final DeleteReceiptUseCase deleteReceiptUseCase;


    @GetMapping("/borra")
    public String deleteReceipt(
            @RequestParam(value="id",defaultValue="0") Integer id
            ,ModelMap model
    ) {

        deleteReceiptUseCase.deleteByIdReceipt(id);
        model.clear();
        return "redirect:/receipts";
    }

    @GetMapping("/delete/{id}")
    public String deleteReceiptById(
            @RequestParam(value="id",defaultValue="0") Integer id
            ,ModelMap model
    ) {

        deleteReceiptUseCase.deleteByIdReceipt(id);
        model.clear();
        return "redirect:/receipts";
    }
}