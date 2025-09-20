package ujaen.daw.springmvcproject.controller;

import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.ui.ModelMap;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import ujaen.daw.springmvcproject.dto.ProductDTO;
import ujaen.daw.springmvcproject.models.Product;
import ujaen.daw.springmvcproject.service.IProductService;

import java.util.List;
import java.util.logging.Logger;

@Controller
@RequestMapping("/products")
public class ProductController {

    @Autowired
    private IProductService productService;

    @ModelAttribute
    public void configView(ModelMap model) {
        model.addAttribute("srvUrl", "/products");
        model.addAttribute("imgUrl", "/images");
    }

    private static final Logger logger = Logger.getLogger(ProductController.class.getName());

    // Listar productos
    @GetMapping(path = {"", "/home"})
    public String listarProductos(Model model) {
        List<ProductDTO> lista = productService.findAll();
        model.addAttribute("productos", lista);
        logger.info("Listando productos");
        return "products/home";
    }

    // Mostrar formulario de creación
    @GetMapping("/add")
    public String addForm(Model model) {
        model.addAttribute("product", new Product());
        return "products/add";
    }

    // Procesar formulario de creación
    @PostMapping("/add")
    public String add(@ModelAttribute("product") @Valid Product product, BindingResult result, Model model) {
        String view = "redirect:/products/home";

        if (!result.hasErrors()) {
            productService.save(product);
            model.asMap().clear();
        } else {
            model.addAttribute("product", product);
            view = "products/add";
        }
        return view;
    }

    // Eliminar producto
    @GetMapping("/delete")
    public String delete(@RequestParam(value = "id", defaultValue = "0") Long id, ModelMap model) {
        if (id != 0) {
            productService.deleteById(id);
            logger.info("Producto con id " + id + " eliminado");
        }
        model.clear();
        return "redirect:/products/home"; // Redirige a la lista de productos después de eliminar
    }

    // Mostrar formulario de edición
    @GetMapping("/edit")
    public String editForm(@RequestParam(value = "id", defaultValue = "0") Long id, ModelMap model) {
        model.addAttribute("product", productService.findById(id));
        return "products/edit";
    }

    // Procesar formulario de edición
    @PostMapping("/edit")
    public String edit(@ModelAttribute("product") @Valid Product product, BindingResult result, ModelMap model) {
        String view = "redirect:/products/home";
        if (!result.hasErrors()) {
            productService.save(product);
            model.clear();
        } else {
            view = "products/edit";
        }
        return view;
    }
}
