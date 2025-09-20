package crm.webservices;

import crm.models.Client;
import crm.persistence.jpa.ClientDAOJPA;
import crm.qualifiers.DAOJpa;
import jakarta.enterprise.context.RequestScoped;
import jakarta.inject.Inject;
import jakarta.ws.rs.GET;
import jakarta.ws.rs.Path;
import jakarta.ws.rs.Produces;
import jakarta.ws.rs.core.Context;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;
import jakarta.ws.rs.core.UriInfo;

import java.util.List;

@Path("clients")
@Produces(MediaType.APPLICATION_JSON)
@RequestScoped
public class ClientRESTService {

    @Context
    private UriInfo context;

    @Inject @DAOJpa
    ClientDAOJPA clientDAO;

    public ClientRESTService() {}

    @GET
    public Response findAll() {
        List<Client> cList = clientDAO.getAllClients();
        return cList != null && !cList.isEmpty()
                ? Response.ok(cList).build()
                : Response.status(Response.Status.NO_CONTENT).build();
    }

}
