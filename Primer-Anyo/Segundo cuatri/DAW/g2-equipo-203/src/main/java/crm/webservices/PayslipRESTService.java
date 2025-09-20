package crm.webservices;

import crm.models.Payslip;
import crm.persistence.IPayslipDAO;
import crm.qualifiers.DAOJpa;
import crm.util.ResponseMessage;
import jakarta.enterprise.context.RequestScoped;
import jakarta.inject.Inject;
import jakarta.validation.Valid;
import jakarta.ws.rs.*;
import jakarta.ws.rs.core.Context;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.core.Response;
import jakarta.ws.rs.core.UriInfo;

import java.util.List;

@Path("payslip")
@Produces(MediaType.APPLICATION_JSON)
@RequestScoped
public class PayslipRESTService {

    @Context
    private UriInfo context;

    @Inject
    @DAOJpa
    private IPayslipDAO payslipDAO;

    public PayslipRESTService() {}

    @GET
    public List<Payslip> getAllPayslips() {
        return payslipDAO.getAllPayslips();
    }

    @GET
    @Path("{id}")
    public Response getPayslipById(@PathParam("id") Long id) {
        Payslip payslip = payslipDAO.getPayslipById(id);
        if (payslip == null) {
            return Response.status(Response.Status.NOT_FOUND)
                    .entity(new ResponseMessage("Nómina no encontrada"))
                    .build();
        }
        return Response.ok(payslip).build();
    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    public Response createPayslip(Payslip payslip) {
        if (payslip == null) {
            return Response.status(Response.Status.BAD_REQUEST)
                    .entity(new ResponseMessage("Datos de la nómina inválidos"))
                    .build();
        }

        payslipDAO.createPayslip(payslip);
        return Response.status(Response.Status.CREATED)
                .entity(new ResponseMessage("Nómina creada con éxito"))
                .build();
    }

    @PUT
    @Path("{id}")
    @Consumes(MediaType.APPLICATION_JSON)
    public Response updatePayslip(@PathParam("id") Long id, @Valid Payslip payslip) {
        if (payslip == null) {
            return Response.status(Response.Status.BAD_REQUEST)
                    .entity(new ResponseMessage("Datos de la nómina inválidos"))
                    .build();
        }

        Payslip existingPayslip = payslipDAO.getPayslipById(id);
        if (existingPayslip == null) {
            return Response.status(Response.Status.NOT_FOUND)
                    .entity(new ResponseMessage("Nómina no encontrada"))
                    .build();
        }

        payslip.setId(id);
        payslipDAO.updatePayslip(payslip);
        return Response.ok(new ResponseMessage("Nómina actualizada con éxito")).build();
    }

    @DELETE
    @Path("{id}")
    public Response deletePayslip(@PathParam("id") Long id) {
        Payslip existingPayslip = payslipDAO.getPayslipById(id);
        if (existingPayslip == null) {
            return Response.status(Response.Status.NOT_FOUND)
                    .entity(new ResponseMessage("Nómina no encontrada"))
                    .build();
        }

        payslipDAO.deletePayslip(id);
        return Response.ok(new ResponseMessage("Nómina eliminada con éxito")).build();
    }
}