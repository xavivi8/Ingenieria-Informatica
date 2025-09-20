package crm.persistence.jpa;

import crm.models.Product;
import crm.models.Receipt;
import crm.models.ReceiptDetails;
import crm.persistence.ReceiptDAO;
import crm.qualifiers.DAOJpa;
import jakarta.enterprise.context.Dependent;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Predicate;
import jakarta.persistence.criteria.Root;
import jakarta.transaction.Transactional;

import java.io.Serializable;
import java.math.BigDecimal;
import java.math.RoundingMode;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

@DAOJpa
@Dependent
@Transactional
public class ReceiptDAOJpa implements ReceiptDAO, Serializable {

    private final Logger logger = Logger.getLogger(ReceiptDAOJpa.class.getName());

    @PersistenceContext(unitName = "crmDB")
    private EntityManager em;

    @Override
    public Receipt create(Receipt r) {
        try {
            r.setDate(LocalDate.now());
            r.setTotalPrice(0.0);
            em.persist(r);
            em.flush();
            return r;
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return null;
    }

    @Override
    public Receipt readById(Integer id) {
        Receipt r = null;
        try {
            r = em.find(Receipt.class, id);
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return r;
    }

    @Override
    public List<Receipt> readAll() {
        List<Receipt> receipts = null;
        try {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Receipt> query = cb.createQuery(Receipt.class);
            Root<Receipt> receiptsRoot = query.from(Receipt.class);
            query.select(receiptsRoot);
            receipts = em.createQuery(query).getResultList();
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return receipts;
    }

    @Override
    public Receipt update(Receipt r) {
        try {
            double total = 0.0;
            if (r.getDetails() != null) {
                for (ReceiptDetails det : r.getDetails()) {
                    Product prod = em.find(Product.class, det.getIdProduct());
                    if (prod == null) {
                        throw new IllegalArgumentException(
                                "Producto " + det.getIdProduct() + " no encontrado");
                    }
                    total += prod.getBase_price() * det.getAmount();
                }
            }
            r.setTotalPrice(
                    new BigDecimal(total).setScale(2, RoundingMode.HALF_UP).doubleValue()
            );

            Receipt updated = em.merge(r);
            em.flush();
            return updated;
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
            return null;
        }
    }

    @Override
    public boolean delete(Integer id) {
        boolean borrado = false;
        try {
            Receipt r = em.find(Receipt.class, id);
            em.remove(r);
            borrado = true;
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return borrado;
    }

    @Override
    public Receipt buscaByCampo(String campo) {
        Receipt r = null;
        try {
            r = em.find(Receipt.class, campo);
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return r;
    }

    @Override
    public boolean save(Receipt r) {
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
    public List<Receipt> readByClientId(Long clientId) {
        try {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Receipt> cq = cb.createQuery(Receipt.class);
            Root<Receipt> root = cq.from(Receipt.class);
            cq.select(root).where(cb.equal(root.get("idClient"), clientId));
            return em.createQuery(cq).getResultList();
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
            return List.of();
        }
    }

    @Override
    public List<Receipt> searchByUserOrClient(Long idUserCrm, Long idClient) {
        try {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Receipt> cq = cb.createQuery(Receipt.class);
            Root<Receipt> root = cq.from(Receipt.class);

            Predicate p1 = null;
            Predicate p2 = null;
            if (idUserCrm != null) {
                p1 = cb.equal(root.get("idUserCrm"), idUserCrm);
            }
            if (idClient != null) {
                p2 = cb.equal(root.get("idClient"), idClient);
            }

            Predicate combined;
            if (p1 != null && p2 != null) {
                combined = cb.or(p1, p2);
            } else if (p1 != null) {
                combined = p1;
            } else if (p2 != null) {
                combined = p2;
            } else {
                combined = cb.conjunction();
            }

            cq.select(root).where(combined);
            return em.createQuery(cq).getResultList();
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
            return List.of();
        }
    }

    @Override
    public List<Receipt> searchByMinPriceOrUser(Long idUserCrm, Double minTotalPrice) {
        try {
            CriteriaBuilder cb = em.getCriteriaBuilder();
            CriteriaQuery<Receipt> cq = cb.createQuery(Receipt.class);
            Root<Receipt> root = cq.from(Receipt.class);

            Predicate p1 = null;
            Predicate p2 = null;
            if (idUserCrm != null) {
                p1 = cb.equal(root.get("idUserCrm"), idUserCrm);
            }
            if (minTotalPrice != null) {
                p2 = cb.ge(root.get("totalPrice"), minTotalPrice);
            }

            Predicate combined;
            if (p1 != null && p2 != null) {
                combined = cb.or(p1, p2);
            } else if (p1 != null) {
                combined = p1;
            } else if (p2 != null) {
                combined = p2;
            } else {
                combined = cb.conjunction();
            }

            cq.select(root).where(combined);
            return em.createQuery(cq).getResultList();
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
            return List.of();
        }
    }

    @Override
    @Transactional
    public Integer deleteByTotalPriceGreaterThan(double threshold) {

        try {
            List<Receipt> targets = em.createQuery(
                            "SELECT r FROM Receipt r WHERE r.totalPrice > :th",
                            Receipt.class)
                    .setParameter("th", threshold)
                    .getResultList();

            for (Receipt r : targets) {
                em.remove(r);
            }
            return targets.size();

        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
            return 0;
        }
    }

    @Override
    public List<Receipt> filter(
            Long      userId
            ,Long      clientId
            ,Double    minTotal
            ,Double    maxTotal
            ,LocalDate startDate
            ,LocalDate endDate
    ) {

        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<Receipt> cq = cb.createQuery(Receipt.class);
        Root<Receipt> root = cq.from(Receipt.class);

        List<Predicate> filters = new ArrayList<>();

        if (userId != null) {
            filters.add(cb.equal(root.get("idUserCrm"), userId));
        }
        if (clientId != null) {
            filters.add(cb.equal(root.get("idClient"), clientId));
        }
        if (minTotal != null) {
            filters.add(cb.ge(root.get("totalPrice"), minTotal));
        }
        if (maxTotal != null) {
            filters.add(cb.le(root.get("totalPrice"), maxTotal));
        }
        if (startDate != null) {
            filters.add(cb.greaterThanOrEqualTo(root.get("date"), startDate));
        }
        if (endDate != null) {
            filters.add(cb.lessThanOrEqualTo(root.get("date"), endDate));
        }

        cq.where(cb.and(filters.toArray(new Predicate[0])))
                .orderBy(cb.desc(root.get("date")));

        return em.createQuery(cq).getResultList();
    }
}
