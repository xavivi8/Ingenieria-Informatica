package crm.controller;

import crm.AppConfig;
import crm.models.ReceiptDetails;
import crm.persistence.jpa.ReceiptDetailsDAOJpa;
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
import java.util.List;
import java.util.logging.Logger;

@Named(value = "receiptDetailsCtrl")
@ViewScoped
@Getter
@Setter
public class ReceiptDetailsController implements Serializable {

    @Serial
    private static final long serialVersionUID = 1L;

    private final Logger logger = Logger.getLogger(ReceiptDetailsController.class.getName());

    @Inject @DAOJpa
    private ReceiptDetailsDAOJpa receiptDetailsDAOJpa;

    @Inject
    FacesContext fc;

    @Inject
    private AppConfig appConfig;

    private List<ReceiptDetails> receiptDetailsList;
    private ReceiptDetails receiptDetails;
    private ReceiptDetails receiptToDelete;

    @PostConstruct
    public void init() {
        receiptDetails = new ReceiptDetails();
    }

    public List<ReceiptDetails> getReceipts() {
        return receiptDetailsDAOJpa.readAll();
    }

    public void recupera() {
        receiptDetails = receiptDetailsDAOJpa.readById(receiptDetails.getId());
        if (receiptDetails == null) {
            fc.addMessage(null, new FacesMessage("Los detalles de factura solicitada no existen"));
        }
    }

    public ReceiptDetails findReceiptDetailsById(Integer idReceiptDetails) {
        return receiptDetailsDAOJpa.readById(idReceiptDetails);
    }
}
