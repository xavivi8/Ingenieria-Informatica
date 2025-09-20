package crm.controller;

import crm.AppConfig;
import crm.enums.PayslipStatus;
import crm.models.Payslip;
import crm.persistence.IPayslipDAO;
import crm.qualifiers.DAOJpa;

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

@Named(value = "payslipCtrl")
@ViewScoped
@Getter
@Setter
public class PayslipController implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;
    private static final Logger logger = Logger.getLogger(PayslipController.class.getName());

    @Inject
    @DAOJpa
    private IPayslipDAO payslipDAO;

    @Inject
    private FacesContext facesContext;

    @Inject
    private SecurityContext securityContext;

    @Inject
    private AppConfig appConfig;

    private Principal principal;
    private Payslip payslip;
    private Payslip payslipEliminar;
    private Payslip payslipAEliminar;
    private PayslipStatus statusSeleccionado;

    @PostConstruct
    public void init() {
        payslip = new Payslip();
        String currentPayslip = "Anónimo";
        principal = securityContext.getCallerPrincipal();
        if (principal != null) {
            currentPayslip = principal.getName();
        }
        logger.info("Current payslip: " + currentPayslip);
        List<Payslip> existentes = payslipDAO.getAllPayslips();
    }

    public List<Payslip> getPayslips() {
        return payslipDAO.getAllPayslips();
    }

    public String crea() {
        payslipDAO.createPayslip(payslip);
        return "/nominas/home.xhtml?faces-redirect=true";
    }

    public String guarda() {
        payslipDAO.updatePayslip(payslip);
        return "/nominas/home?faces-redirect=true";
    }

    public void preparareliminacion(Payslip p) {
        this.payslipAEliminar = p;
    }

    public void confirmarEliminacion() {
        if (payslipAEliminar != null) {
            payslipDAO.deletePayslip(payslipAEliminar.getId());
            FacesContext.getCurrentInstance().addMessage(null,
                    new FacesMessage("Nomina eliminada correctamente"));
            payslipAEliminar = null;
        }
    }

    public String eliminar(Payslip p) {
        payslipDAO.deletePayslip(payslip.getId());
        facesContext.addMessage(null, new FacesMessage("Nómina eliminada"));
        return "listado";
    }

    public void editRow(Payslip p) {
        this.payslip = p;
    }

    public void cancelEditRow() {
        this.payslip = new Payslip();
    }

    public void recuperaPayslip() {
        payslip = payslipDAO.getPayslipById(payslip.getId());
        if (payslip != null) {
            facesContext.addMessage(null, new FacesMessage("Payslip recuperado"));
        }
    }

    public PayslipStatus[] getTodosLosEstados() {
        return PayslipStatus.values();
    }

    // Método para eliminar nóminas según el estado seleccionado
    public void eliminarPorEstado() {
        if (statusSeleccionado != null) {
            payslipDAO.deletePayslipsByStatus(statusSeleccionado);
            FacesContext.getCurrentInstance().addMessage(null,
                    new FacesMessage("Nóminas con estado " + statusSeleccionado + " eliminadas correctamente"));
        }
    }
}
