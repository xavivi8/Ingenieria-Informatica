package daw.app.rest;

import daw.app.service.NotificacionService;
import jakarta.inject.Inject;
import jakarta.inject.Singleton;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.ws.rs.GET;
import jakarta.ws.rs.Path;
import jakarta.ws.rs.Produces;
import jakarta.ws.rs.core.Context;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.sse.Sse;
import jakarta.ws.rs.sse.SseEventSink;

@Path("/events")
@Singleton
public class SseResource {

    @Inject
    private NotificacionService notificacionService;

    @GET
    @Produces(MediaType.SERVER_SENT_EVENTS)
    public void stream(@Context SseEventSink sink, @Context Sse sse, @Context HttpServletRequest request) {
        String nombreUsuario = request.getRemoteUser(); // usuario logueado
        notificacionService.addCliente(sink, sse, nombreUsuario);
    }
}
