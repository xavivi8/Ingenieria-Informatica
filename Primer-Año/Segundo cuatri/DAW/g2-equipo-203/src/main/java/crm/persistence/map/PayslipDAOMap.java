package crm.persistence.map;

import crm.enums.PayslipStatus;
import crm.models.Client;
import crm.models.Payslip;
import crm.persistence.IPayslipDAO;
import crm.qualifiers.DAOMap;
import jakarta.enterprise.context.ApplicationScoped;
import jakarta.persistence.EntityManager;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@ApplicationScoped
@DAOMap
public class PayslipDAOMap  implements IPayslipDAO, Serializable {

    private final Map<Long,Payslip> payslips;
    private Long payslipId=1L;

    public PayslipDAOMap() {
        payslips = new HashMap<>();
    }
    @Override
    public void createPayslip(Payslip p) {
    Payslip newPayslip = new Payslip(p);
    newPayslip.setId(payslipId);
    payslips.put(payslipId, newPayslip);
    p.setId(payslipId);
    payslipId++;
    }

    @Override
    public Payslip getPayslipById(Long id) {
      Payslip payslip = payslips.get(id);
      return payslip != null ? new Payslip(payslip) : null;
    }

    @Override
    public List<Payslip> getAllPayslips() {
        return payslips.values().stream().map(Payslip::new ).collect(Collectors.toList());
    }

    @Override
    public void updatePayslip(Payslip p) {
   if (payslips.containsKey(p.getId())) {
       Payslip updated = new Payslip(p);
       payslips.replace(p.getId(), updated);
   }
    }

    @Override
    public void deletePayslip(Long id) {
    payslips.remove(id);
    }

    @Override
    public void deletePayslipsByStatus( PayslipStatus status) {

    }
}
