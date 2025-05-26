package crm.persistence.jpa;

import crm.models.Product;
import crm.models.User;
import crm.persistence.IProductDAO;
import crm.persistence.IUserDAO;
import crm.qualifiers.DAOJpa;
import jakarta.enterprise.context.Dependent;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import jakarta.persistence.TypedQuery;
import jakarta.transaction.Transactional;

import java.io.Serializable;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

@Dependent
@DAOJpa
@Transactional
public class ProductDAOJPA implements IProductDAO, Serializable {

    private final Logger logger = Logger.getLogger(ProductDAOJPA.class.getName());

    @PersistenceContext(unitName = "crmDB")
    private EntityManager em;

    public ProductDAOJPA() {}


    @Override
    public void createProduct(Product product) {
        try{
            em.persist(product);
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
    }

    @Override
    public Product getProductById(Long id) {
        Product product = null;
        try{
            product = em.find(Product.class, id);
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return product;
    }

    @Override
    public List<Product> getAllProducts() {
        List<Product> products = null;
        try{
            TypedQuery<Product> q = em.createQuery("SELECT p FROM Product p", Product.class);
            products = q.getResultList();
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
        return products;
    }

    @Override
    public void updateProduct(Product product) {
        try{
            em.merge(product);
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
    }

    @Override
    public void deleteProduct(Long id) {
        try{
            Product product = em.find(Product.class, id);
            if (product != null) {
                em.remove(product);
            }
        } catch (Exception ex) {
            logger.log(Level.SEVERE, ex.getMessage(), ex);
        }
    }
}
