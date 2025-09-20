package crm.webservices;

import crm.models.Product;
import crm.persistence.IProductDAO;
import crm.qualifiers.DAOJpa;
import crm.util.ResponseMessage;
import jakarta.enterprise.context.RequestScoped;
import jakarta.inject.Inject;
import jakarta.ws.rs.*;
import jakarta.ws.rs.core.Context;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;
import jakarta.ws.rs.core.UriInfo;

import java.util.List;

@Path("product")
@Produces(MediaType.APPLICATION_JSON)

@RequestScoped
public class ProductRESTService {

    @Context
    private UriInfo context;

    @Inject
    @DAOJpa
    private IProductDAO productDAO;

    public ProductRESTService() {}

    @GET
    public List<Product> getAllProducts() {
        return productDAO.getAllProducts();
    }

    @GET
    @Path("{id}")
    public Response getProductById(@PathParam("id") Long id) {
        Product product = productDAO.getProductById(id);
        if (product == null) {
            return Response.status(Response.Status.NOT_FOUND).entity("Producto no encontrado").build();
        }
        return Response.ok(product).build();
    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public Response createProduct(Product product) {
        if (product == null) {
            return Response.status(Response.Status.BAD_REQUEST)
                    .entity(new ResponseMessage("Datos del producto inválidos"))
                    .build();
        }

        productDAO.createProduct(product);

        // Devolver la respuesta en formato JSON
        return Response.status(Response.Status.CREATED)
                .entity(new ResponseMessage("Producto creado con éxito"))
                .build();
    }


    @PUT
    @Path("{id}")
    @Consumes(MediaType.APPLICATION_JSON)
    public Response updateProduct(@PathParam("id") Long id, Product product) {

        // Validación básica
        if (product == null) {
            return Response.status(Response.Status.BAD_REQUEST)
                    .entity(new ResponseMessage("Datos del producto inválidos"))
                    .build();
        }

        Product existingProduct = productDAO.getProductById(id);
        if (existingProduct == null) {
            return Response.status(Response.Status.NOT_FOUND)
                    .entity(new ResponseMessage("Producto no encontrado"))
                    .build();
        }

        // Actualizar y devolver resultado
        product.setId(id);
        productDAO.updateProduct(product);
        return Response.ok(new ResponseMessage("Producto actualizado con éxito")).build();
    }

    @DELETE
    @Path("{id}")
    public Response deleteProduct(@PathParam("id") Long id) {
        Product existingProduct = productDAO.getProductById(id);
        if (existingProduct == null) {
            // Devolver un mensaje en JSON con el error
            return Response.status(Response.Status.NOT_FOUND)
                    .entity(new ResponseMessage("Producto no encontrado"))
                    .build();
        }

        productDAO.deleteProduct(id);

        // Devolver un mensaje en formato JSON
        return Response.ok(new ResponseMessage("Producto eliminado con éxito")).build();
    }
}
