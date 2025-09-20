package crm.controller;

import crm.models.Product;
import crm.models.Receipt;
import crm.persistence.IProductDAO;
import crm.qualifiers.DAOJpa;
import crm.qualifiers.DAOMap;
import jakarta.annotation.PostConstruct;
import jakarta.faces.application.FacesMessage;
import jakarta.faces.context.FacesContext;
import jakarta.faces.view.ViewScoped;
import jakarta.inject.Inject;
import jakarta.inject.Named;
import jakarta.security.enterprise.SecurityContext;
import lombok.Getter;
import lombok.Setter;

import java.io.Serial;
import java.io.Serializable;
import java.security.Principal;
import java.util.List;
import java.util.logging.Logger;

@Named(value = "productCtrl")
@ViewScoped
@Getter
@Setter
public class ProductController implements Serializable {

    @Serial
    private static final long serialVersionUID = 1L;

    private static Logger logger = Logger.getLogger(ProductController.class.getName());

    //@Inject @DAOMap
    @Inject @DAOJpa
    private IProductDAO productDAO;

    @Inject
    private FacesContext fc;

    @Inject
    private SecurityContext sc;

    private Product product;
    private Principal principal;
    private Product productAEliminar;

    @PostConstruct
    private void init() {
        product = new Product();

        String currentUser = "Anónimo";
        principal = sc.getCallerPrincipal();

        if (principal != null) {
            currentUser = principal.getName();
        }

        logger.info("Petición de productos: " + currentUser);
        List<Product> products = productDAO.getAllProducts();
    }

    public List<Product> getProducts() {
        return productDAO.getAllProducts();
    }

    public String crea(){
        productDAO.createProduct(product);
        return "/product/home.xhtml?faces-redirect=true";
    }

    public Product findById(Long id){
        return productDAO.getProductById(id);
    }

    public void prepararEliminacion(Product product) {
        this.productAEliminar = product;
    }

    public void confirmarEliminacion(){
        if (productAEliminar != null) {
            productDAO.deleteProduct(productAEliminar.getId());
            fc.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_INFO, "Producto eliminado correctamente", ""));
            productAEliminar = null;
        } else {
            fc.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_ERROR, "Error al eliminar el producto", ""));
        }
    }

    public void incrementarStock(Product p) {
        p.setStock(p.getStock() + 1);
        productDAO.updateProduct(p);
        fc.addMessage(null, new FacesMessage("Stock incrementado"));
    }

    public void disminuirStock(Product p) {
        if (p.getStock() > 0) {
            p.setStock(p.getStock() - 1);
            productDAO.updateProduct(p);
            fc.addMessage(null, new FacesMessage("Stock disminuido"));
        } else {
            fc.addMessage(null, new FacesMessage(FacesMessage.SEVERITY_WARN, "Stock ya está en 0", ""));
        }
    }

    public void recupera(){
        product = productDAO.getProductById(product.getId());
        if(product == null){
            fc.addMessage(null, new FacesMessage("El producto indicado no existe"));
        }
    }

    public String guarda(){
        productDAO.updateProduct(product);
        return "/product/home.xhtml?faces-redirect=true";
    }

    public String borra(Product product) {
        productDAO.deleteProduct(product.getId());
        fc.addMessage(null, new FacesMessage("Producto eliminado correctamente"));
        return "home?faces-redirect=true";
    }

}
