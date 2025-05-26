package crm.persistence.map;

import crm.models.Client;
import crm.persistence.IClientDAO;
import crm.qualifiers.DAOMap;
import jakarta.enterprise.context.ApplicationScoped;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@ApplicationScoped
@DAOMap
public class ClientDAOMap implements IClientDAO, Serializable {

    private final Map<Long, Client> clients;
    private Long currentId = 1L;

    public ClientDAOMap() {
        clients = new HashMap<>();
    }

    @Override
    public void createClient(Client client) {
        Client newClient = new Client(client);
        newClient.setId(currentId);
        clients.put(currentId, newClient);
        client.setId(currentId);
        currentId++;
    }

    @Override
    public Client getClientById(Long id) {
        Client client = clients.get(id);
        return client != null ? new Client(client) : null;
    }

    @Override
    public List<Client> getAllClients() {
        return clients.values().stream().map(Client::new).collect(Collectors.toList());
    }

    @Override
    public void updateClient(Client client) {
        if (clients.containsKey(client.getId())) {
            Client updated = new Client(client);
            clients.replace(client.getId(), updated);
        }
    }

    @Override
    public void deleteClient(Long id) {
        clients.remove(id);
    }

    public int clientCount() {
        return clients.size();
    }
}
