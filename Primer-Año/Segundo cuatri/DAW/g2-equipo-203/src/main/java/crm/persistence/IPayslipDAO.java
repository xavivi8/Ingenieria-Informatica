package crm.persistence;

import crm.enums.PayslipStatus;
import crm.models.Payslip;

import java.util.List;

public interface IPayslipDAO {

    void createPayslip(Payslip p);

    Payslip getPayslipById(Long id);

    List<Payslip> getAllPayslips();

    void updatePayslip(Payslip p);

    void deletePayslip(Long id);

    public void deletePayslipsByStatus(PayslipStatus status);
}
