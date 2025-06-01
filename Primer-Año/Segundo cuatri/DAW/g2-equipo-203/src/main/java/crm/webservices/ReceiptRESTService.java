package crm.webservices;

import crm.models.Receipt;
import crm.models.ReceiptDetails;
import crm.models.dto.input.ReceiptCreateInputDTO;
import crm.models.dto.input.ReceiptUpdateInputDTO;
import crm.persistence.ReceiptDAO;
import crm.persistence.ReceiptDetailsDAO;
import crm.qualifiers.DAOJpa;
import jakarta.enterprise.context.RequestScoped;
import jakarta.inject.Inject;
import jakarta.validation.Valid;
import jakarta.ws.rs.*;
import jakarta.ws.rs.core.Context;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;
import jakarta.ws.rs.core.UriInfo;

import java.util.ArrayList;
import java.util.List;

@Path("receipts")
@Produces(MediaType.APPLICATION_JSON)
@RequestScoped
public class ReceiptRESTService {

    @Context
    private UriInfo context;

    @Inject @DAOJpa
    ReceiptDAO receiptDAO;
    @Inject @DAOJpa
    ReceiptDetailsDAO receiptDetailsDAO;

    public ReceiptRESTService() {}

    @GET
    public Response findAll() {
        List<Receipt> rList = receiptDAO.readAll();
        return rList != null && !rList.isEmpty()
                ? Response.ok(rList).build()
                : Response.status(Response.Status.NO_CONTENT).build();
    }

    @GET
    @Path("/{id}")
    public Response findById(@PathParam("id") Integer id) {
        Receipt r = receiptDAO.readById(id);
        if (r != null) {
            return Response.ok(r).build();
        } else return Response.status(Response.Status.NOT_FOUND).build();
    }

    @DELETE
    @Path("/{id}")
    public Response delete(@PathParam("id") Integer id) {
        if (!receiptDAO.delete(id)) {
            return Response.status(Response.Status.BAD_REQUEST).build();
        }
        return Response.ok().build();
    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public Response create(@Valid ReceiptCreateInputDTO receiptDto) {

        List<ReceiptDetails> receiptDetailsList = new ArrayList<>();
        receiptDto.getDetails().forEach(rdDto -> {
            receiptDetailsList.add(
                    receiptDetailsDAO.create(
                            new ReceiptDetails(
                                    rdDto.getIdProduct()
                                    ,rdDto.getAmount()
                            )
                    )
            );
        });

        Receipt newReceipt = new Receipt(
                receiptDto.getIdUserCrm()
                ,receiptDto.getIdClient()
                ,receiptDetailsList
        );

        Receipt createdReceipt = receiptDAO.create(newReceipt);
        return createdReceipt.getId() != null
                ? Response.ok(createdReceipt.getId()).build()
                : Response.status(Response.Status.NO_CONTENT).build();
    }

    @PUT
    @Consumes(MediaType.APPLICATION_JSON)
    public Response update(@Valid ReceiptUpdateInputDTO receiptDto) {

        Receipt receiptToUpdate = receiptDAO.readById(receiptDto.getIdReceipt());

        if (receiptDto.getIdClient() != null) {
            receiptToUpdate.setIdClient(receiptDto.getIdClient());
        }
        if (receiptDto.getIdUserCrm() != null) {
            receiptToUpdate.setIdUserCrm(receiptDto.getIdUserCrm());
        }

        return receiptDAO.update(receiptToUpdate).getId() != null
                ? Response.ok().build()
                : Response.status(Response.Status.BAD_REQUEST).build();
    }
}
