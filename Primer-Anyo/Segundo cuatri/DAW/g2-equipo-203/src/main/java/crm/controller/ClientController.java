package crm.controller;

import crm.AppConfig;
import crm.models.Client;
import crm.persistence.IClientDAO;
import crm.qualifiers.DAOJpa;
import crm.qualifiers.DAOMap;
import jakarta.annotation.PostConstruct;
import jakarta.faces.application.FacesMessage;
import jakarta.faces.context.FacesContext;
import jakarta.faces.view.ViewScoped;
import jakarta.inject.Inject;
import jakarta.inject.Named;
import jakarta.security.enterprise.SecurityContext;
import lombok.Getter;
import lombok.Setter;

import java.io.Serial;
import java.io.Serializable;
import java.security.Principal;
import java.util.List;
import java.util.logging.Logger;


@Named(value = "clientCtrl")
@ViewScoped
@Getter
@Setter
public class ClientController implements Serializable {
    @Serial
    private static final long serialVersionUID = 1L;
    private static final Logger logger = Logger.getLogger(ClientController.class.getName());



    @Inject @DAOJpa

    private IClientDAO clientDao;

    @Inject
    private FacesContext fc;

    @Inject
    private SecurityContext sc;

    @Inject
    private AppConfig appConfig;

    private Principal principal;
    private Client client;
    private Client clientEliminar;

    @PostConstruct
    public void init() {
        client = new Client();
        String currentclient = "Anónimo";
        principal = sc.getCallerPrincipal();
        if (principal != null) {
            currentclient = principal.getName();
        }
        logger.info("Peticion de cliente" + currentclient);
    }

    public Client buscaClientPorId(Long idClient) {
        return clientDao.getClientById(idClient);
    }

    public List<Client> getClients() {
        return clientDao.getAllClients();
    }

    public void recuperar() {
        client = clientDao.getClientById(client.getId());
        if (client == null) {
            fc.addMessage(null, new FacesMessage("Cliente no encontrado"));
        }
    }

    public String crea() {
        clientDao.createClient(client);
        return "/client/home.xhtml?faces-redirect=true";
    }

    public String guarda() {
        clientDao.updateClient(client);
        return "/client/home.xhtml?faces-redirect=true&id=" + client.getId();
    }

    public void preparareliminacion(Client client) {
        this.clientEliminar = client;
    }

    public void confirmarEliminacion() {
        if (clientEliminar != null) {
            clientDao.deleteClient(clientEliminar.getId());
        }
    }

    public String borra() {
        clientDao.deleteClient(client.getId());
        fc.addMessage(null, new FacesMessage("Cliente eliminado"));
        return "listado";
    }

    public void editRow(Client client) {
        this.client = client;
    }

    public void cancelEditRow() {
        this.client = new Client();
    }

    public void actualizar() {
        clientDao.updateClient(client);
        cancelEditRow();
    }


}
