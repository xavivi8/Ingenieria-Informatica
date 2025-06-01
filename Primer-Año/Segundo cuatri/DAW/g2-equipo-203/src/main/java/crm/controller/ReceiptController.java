package crm.controller;

import crm.AppConfig;
import crm.models.Product;
import crm.models.Receipt;
import crm.models.ReceiptDetails;
import crm.persistence.jpa.ReceiptDAOJpa;
import crm.persistence.jpa.ReceiptDetailsDAOJpa;
import crm.persistence.IProductDAO;
import crm.qualifiers.DAOJpa;
import jakarta.annotation.PostConstruct;
import jakarta.faces.application.FacesMessage;
import jakarta.faces.context.FacesContext;
import jakarta.faces.view.ViewScoped;
import jakarta.inject.Inject;
import jakarta.inject.Named;
import lombok.Getter;
import lombok.Setter;

import java.io.Serial;
import java.io.Serializable;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;

@Named(value = "receiptCtrl")
@ViewScoped
@Getter
@Setter
public class ReceiptController implements Serializable {

    @Serial
    private static final long serialVersionUID = 1L;

    private final Logger logger = Logger.getLogger(ReceiptController.class.getName());

    @Inject @DAOJpa
    private ReceiptDAOJpa receiptDAOJpa;

    @Inject @DAOJpa
    private IProductDAO productDAO;

    @Inject @DAOJpa
    private ReceiptDetailsDAOJpa receiptDetailsDAO;

    @Inject
    FacesContext fc;

    @Inject
    private AppConfig appConfig;

    private List<Receipt> receipts;
    private List<Receipt> receiptsSearched;
    private Receipt receipt;
    private ReceiptDetails receiptDetails;
    private Receipt receiptToDelete;
    private final Map<Long, Object> productQuantities = new HashMap<>();
    private Long clienteId;
    private List<Receipt> facturasCliente = new ArrayList<>();

    // Criteria API
    private Long  searchUserId;
    private Long  searchClientId;
    private Double greaterThanTotalPrice;
        // Filter
        // idUser
        // idClient
        private Double minTotalPrice;
        private Double maxTotalPrice;
        private LocalDate startDate;
        private LocalDate endDate;


    @PostConstruct
    public void init() {
        receipt = new Receipt();
        receiptDetails = new ReceiptDetails();
        receipts = receiptDAOJpa.readAll();
    }

    public List<Receipt> getReceipts() {
        return receiptDAOJpa.readAll();
    }

    public void recover() {
        receipt = receiptDAOJpa.readById(receipt.getId());
        if (receipt == null) {
            fc.addMessage(null, new FacesMessage("La factura solicitada no existe"));
        }
    }

    public String create() {
        receiptDAOJpa.create(receipt);
        fc.addMessage(null, new FacesMessage("Factura creada con éxito"));
        return "/receipt/read.xhtml?faces-redirect=true&id=" + receipt.getId();
    }

    public String save() {
        receiptDAOJpa.save(receipt);
        return "home?faces-redirect=true&id=" + receipt.getId();
    }

    public String delete(Receipt receipt) {
        receiptDAOJpa.delete(receipt.getId());
        fc.addMessage(null, new FacesMessage("Factura eliminada correctamente"));
        return "home?faces-redirect=true";
    }

    public void cargarFacturasCliente(Long id) {
        clienteId = id;
        facturasCliente = (clienteId != null)
                ? receiptDAOJpa.readByClientId(clienteId)
                : new ArrayList<>();
    }

    public void calculateTotal() {
        double total = 0.0;
        receipt.getDetails().clear();

        for (Map.Entry<Long, Object> e : productQuantities.entrySet()) {
            int qty = Integer.parseInt(e.getValue().toString());
            if (qty > 0) {
                Product prod = productDAO.getProductById(e.getKey());
                ReceiptDetails det = new ReceiptDetails();
                det.setIdProduct(prod.getId());
                det.setAmount(qty);
                receipt.getDetails().add(det);
                total += prod.getBase_price() * qty;
            }
        }

        receipt.setTotalPrice(total);
    }

    public void searchByUserOrClient() {
        receiptsSearched = receiptDAOJpa.searchByUserOrClient(searchUserId, searchClientId);
    }
    public void deleteGreaterThanTotalPrice() {
        Integer deletedRows = receiptDAOJpa.deleteByTotalPriceGreaterThan(greaterThanTotalPrice);
        searchByUserOrClient();
    }
    public void searchByFilters() {
        receiptsSearched = receiptDAOJpa.filter(
                searchUserId
                ,searchClientId
                ,minTotalPrice
                ,maxTotalPrice
                ,startDate
                ,endDate
        );
    }

    public List<Product> getSelectedProducts() {
        List<Product> sel = new ArrayList<>();
        for (Map.Entry<Long, Object> e : productQuantities.entrySet()) {
            int qty = Integer.parseInt(e.getValue().toString());
            if (qty > 0) {
                sel.add(productDAO.getProductById(e.getKey()));
            }
        }
        return sel;
    }

}