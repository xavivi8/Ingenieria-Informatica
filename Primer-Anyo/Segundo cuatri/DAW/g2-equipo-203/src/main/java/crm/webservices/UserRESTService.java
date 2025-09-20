package crm.webservices;

import crm.models.User;
import crm.persistence.jpa.UserDAOJPA;
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

@Path("users")
@Produces(MediaType.APPLICATION_JSON)
@RequestScoped
public class UserRESTService {

    @Context
    private UriInfo context;

    @Inject @DAOJpa
    UserDAOJPA userDAO;

    public UserRESTService() {}

    @GET
    public Response findAll() {
        List<User> uList = userDAO.getAllUsers();
        return uList != null && !uList.isEmpty()
                ? Response.ok(uList).build()
                : Response.status(Response.Status.NO_CONTENT).build();
    }

}
