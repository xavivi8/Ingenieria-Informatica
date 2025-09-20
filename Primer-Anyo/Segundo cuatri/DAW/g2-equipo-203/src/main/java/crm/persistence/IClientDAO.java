package crm.persistence;
import crm.models.Client;


import java.util.List;

public interface IClientDAO {
    void createClient(Client client);

    Client getClientById(Long id);

    List<Client> getAllClients();

    void updateClient(Client client);

    void deleteClient(Long id);
}
