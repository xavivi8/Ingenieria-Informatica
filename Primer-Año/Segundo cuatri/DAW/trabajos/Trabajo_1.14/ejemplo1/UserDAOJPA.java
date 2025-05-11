package crm.persistence.jpa;

import crm.models.Payslip;
import crm.models.User;
import crm.persistence.IUserDAO;
import crm.qualifiers.DAOJpa;
import crm.service.PasswordHashService;
import jakarta.enterprise.context.Dependent;
import jakarta.inject.Inject;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import jakarta.persistence.TypedQuery;
import jakarta.persistence.criteria.*;
import jakarta.transaction.Transactional;

import java.io.Serializable;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

@Dependent
@DAOJpa
@Transactional
public class UserDAOJPA implements IUserDAO, Serializable {

    private final Logger logger = Logger.getLogger(UserDAOJPA.class.getName());

    @Inject
    private PasswordHashService passwordHashService;

    @PersistenceContext(unitName = "crmDB")
    private EntityManager em;

    public UserDAOJPA() {
    }

    @Override
    public void deleteUser(Long id) {
        try {
            /* ──────────── 1. Eliminar las nóminas del usuario ──────────── */
            CriteriaBuilder cb = em.getCriteriaBuilder();

            CriteriaDelete<Payslip> deletePayslip = cb.createCriteriaDelete(Payslip.class);
            Root<Payslip> root = deletePayslip.from(Payslip.class);
            deletePayslip.where(cb.equal(root.get("userID"), id));

            // devuelve nº de filas afectadas; no lo necesitamos, pero ejecuta la orden
            em.createQuery(deletePayslip).executeUpdate();

            /* ──────────── 2. Eliminar el propio usuario ──────────── */
            User user = em.find(User.class, id);
            if (user != null) {
                em.remove(user);
            }
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
    }

    @Override
    public boolean login(String email, String password) {
        try {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Long> cq = cb.createQuery(Long.class);
            Root<User> root = cq.from(User.class);

            // Aplicamos la condición de email y contraseña
            Predicate emailPredicate = cb.equal(root.get("email"), email);
            Predicate passwordPredicate = cb.equal(root.get("password"), password);

            // Creamos la consulta de agregación
            cq.select(cb.count(root)).where(cb.and(emailPredicate, passwordPredicate));

            // Ejecutamos la consulta
            TypedQuery<Long> query = em.createQuery(cq);
            Long count = query.getSingleResult();

            return count != null && count > 0;
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
            return false;
        }
    }

}
