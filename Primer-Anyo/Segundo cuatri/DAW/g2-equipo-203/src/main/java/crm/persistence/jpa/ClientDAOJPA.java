package crm.persistence.jpa;

import crm.models.Client;
import crm.persistence.IClientDAO;
import crm.qualifiers.DAOJpa;

import jakarta.enterprise.context.Dependent;
import jakarta.enterprise.context.RequestScoped;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;

import jakarta.persistence.TypedQuery;
import jakarta.transaction.Transactional;

import java.io.Serializable;
import java.util.List;
import java.util.logging.Logger;
import java.util.logging.Level;

//@RequestScoped
@DAOJpa
@Transactional
@Dependent
public class ClientDAOJPA implements IClientDAO, Serializable {


    private final Logger logger = Logger.getLogger(ClientDAOJPA.class.getName());


    @PersistenceContext(unitName = "crmDB")
    private EntityManager em;


    @Override
    public void createClient(Client client) {

      try{
          em.persist(client);
          em.flush();
      }catch(Exception e){
          logger.log(Level.SEVERE, e.getMessage(), e);
      }

    }

    @Override
    public Client getClientById(Long id) {
        return em.find(Client.class, id);
    }

    @Override
    public List<Client> getAllClients() {
       List<Client> client= null;
       try{
           TypedQuery<Client> query = em.createQuery("SELECT c FROM Client c", Client.class);

           client = query.getResultList();

       }catch(Exception e){
           logger.log(Level.SEVERE, e.getMessage(), e);
       }
       return client;
    }

    @Override
    public void updateClient(Client client) {
try{
    em.merge(client);
}catch(Exception e){
logger.log(Level.SEVERE, e.getMessage(), e);
}
    }

    @Override
    public void deleteClient(Long id) {
    try {
        Client client = em.find(Client.class, id);
        if(client != null) {
            em.remove(client);
        }
    }catch(Exception e){
        logger.log(Level.SEVERE, e.getMessage(), e);
    }
    }
}
