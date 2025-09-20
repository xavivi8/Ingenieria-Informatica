package crm.persistence.jpa;

import crm.enums.PayslipStatus;
import crm.models.Payslip;
import crm.persistence.IPayslipDAO;
import crm.qualifiers.DAOJpa;
import jakarta.enterprise.context.Dependent;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import jakarta.persistence.TypedQuery;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaDelete;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Root;
import jakarta.transaction.Transactional;

import java.io.Serializable;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

@Dependent
@DAOJpa
@Transactional
public class PayslipDAOJPA implements IPayslipDAO, Serializable {

    private final Logger logger = Logger.getLogger(PayslipDAOJPA.class.getName());

    @PersistenceContext(unitName = "crmDB")
    private EntityManager em;

    @Override
    public void createPayslip(Payslip p) {
        try {
            em.persist(p);
        } catch (Exception e) {
            logger.log(Level.SEVERE, e.getMessage());
        }
    }

    @Override
    public Payslip getPayslipById(Long id) {
        return em.find(Payslip.class, id);
    }

    @Override
    public List<Payslip> getAllPayslips() {
        List<Payslip> payslips = null;
        try {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Payslip> cq = cb.createQuery(Payslip.class);
            Root<Payslip> root = cq.from(Payslip.class);
            cq.select(root);

            payslips = em.createQuery(cq).getResultList();
        } catch (Exception e) {
            logger.log(Level.SEVERE, e.getMessage(), e);
        }
        return payslips;
    }


    @Override
    public void updatePayslip(Payslip p) {
        try {
            em.merge(p);
        } catch (Exception e) {
            logger.log(Level.SEVERE, e.getMessage());
        }
    }

    @Override
    public void deletePayslip(Long id) {
        try {
            Payslip p = em.find(Payslip.class, id);
            if (p != null) {
                em.remove(p);
            }
        } catch (Exception e) {
            logger.log(Level.SEVERE, e.getMessage());
        }
    }

    @Override
    public void deletePayslipsByStatus(PayslipStatus status) {
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaDelete<Payslip> delete = cb.createCriteriaDelete(Payslip.class);
        Root<Payslip> root = delete.from(Payslip.class);

        delete.where(cb.equal(root.get("status"), status));

        int deleted = em.createQuery(delete).executeUpdate();
        System.out.println("Nóminas eliminadas: " + deleted);
    }
}


