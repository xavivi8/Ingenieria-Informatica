package crm.persistence.jpa;

import crm.models.ReceiptDetails;
import crm.persistence.ReceiptDetailsDAO;
import crm.qualifiers.DAOJpa;
import jakarta.enterprise.context.Dependent;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import jakarta.transaction.Transactional;

import java.io.Serializable;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

@DAOJpa
@Dependent
@Transactional
public class ReceiptDetailsDAOJpa implements ReceiptDetailsDAO, Serializable {

    private final Logger logger = Logger.getLogger(ReceiptDetailsDAOJpa.class.getName());

    @PersistenceContext(unitName = "crmDB")
    private EntityManager em;

    @Override
    public ReceiptDetails create(ReceiptDetails rd) {
        try {
            em.persist(rd);
            em.flush();
            return rd;
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return null;
    }

    @Override
    public ReceiptDetails readById(Integer id) {
        ReceiptDetails r = null;
        try {
            r = em.find(ReceiptDetails.class, id);
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return r;
    }

    @Override
    public List<ReceiptDetails> readAll() {
        List<ReceiptDetails> lc = null;
        try {
            lc = em.createQuery("Select r from ReceiptDetails r", ReceiptDetails.class).getResultList();
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return lc;
    }

    @Override
    public ReceiptDetails update(ReceiptDetails rd) {
        ReceiptDetails updated=null;
        try {
            updated = em.merge(rd);
            em.flush();
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return updated;
    }

    @Override
    public boolean delete(Integer id) {
        boolean borrado = false;
        try {
            ReceiptDetails r = em.find(ReceiptDetails.class, id);
            em.remove(r);
            borrado = true;
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return borrado;
    }

    @Override
    public ReceiptDetails buscaByCampo(String campo) {
        ReceiptDetails r = null;
        try {
            r = em.find(ReceiptDetails.class, campo);
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return r;
    }

    @Override
    public boolean save(ReceiptDetails r) {
        boolean guardado = false;
        try {
            em.merge(r);
            guardado = true;
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return guardado;
    }

    @Override
    public List<ReceiptDetails> findByIdReceipt(Integer idReceipt) {
        List<ReceiptDetails> resultados = null;
        try {
            resultados = em.createQuery(
                            "SELECT rd FROM ReceiptDetails rd WHERE rd.idReceipt = :idReceipt",
                            ReceiptDetails.class)
                    .setParameter("idReceipt", idReceipt)
                    .getResultList();
        } catch (Exception ex) {
            logger.log(Level.SEVERE, "Error en findByIdReceipt para idReceipt=" + idReceipt, ex);
        }
        return resultados;
    }

}
