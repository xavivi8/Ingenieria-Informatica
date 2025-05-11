package daw.app.service;

import jakarta.enterprise.context.ApplicationScoped;
import jakarta.ws.rs.sse.Sse;
import jakarta.ws.rs.sse.SseEventSink;
import jakarta.ws.rs.sse.OutboundSseEvent;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

@ApplicationScoped
public class NotificacionService {

    private final Map<SseEventSink, String> clientes = new ConcurrentHashMap<>();
    private Sse sse;

    public void addCliente(SseEventSink sink, Sse sse, String nombreUsuario) {
        this.sse = sse;
        clientes.put(sink, nombreUsuario);
    }

    public void enviarMensaje(String mensaje, String emisor) {
        if (sse == null) return;

        OutboundSseEvent evento = sse.newEventBuilder()
                .name("mensaje")
                .data(String.class, mensaje)
                .build();

        clientes.forEach((sink, usuario) -> {
            if (!sink.isClosed()) {
                if (!usuario.equals(emisor)) {
                    sink.send(evento);
                }
            } else {
                clientes.remove(sink);
            }
        });
    }
}
