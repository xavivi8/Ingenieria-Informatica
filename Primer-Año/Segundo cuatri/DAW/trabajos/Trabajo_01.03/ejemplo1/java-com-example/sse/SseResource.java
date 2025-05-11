package com.example.sse;

import jakarta.inject.Singleton;
import jakarta.ws.rs.GET;
import jakarta.ws.rs.Path;
import jakarta.ws.rs.Produces;
import jakarta.ws.rs.core.Context;
import jakarta.ws.rs.core.MediaType;
import jakarta.ws.rs.sse.OutboundSseEvent;
import jakarta.ws.rs.sse.Sse;
import jakarta.ws.rs.sse.SseEventSink;

@Path("/events")
@Singleton
public class SseResource {

    @GET
    @Produces(MediaType.SERVER_SENT_EVENTS)
    public void stream(@Context SseEventSink sink, @Context Sse sse) {
        new Thread(() -> {
            try (SseEventSink session = sink) {
                // Enviar 10 eventos “data”
                for (int i = 1; i <= 10; i++) {
                    session.send(sse.newEventBuilder()
                            .name("mensaje")
                            .data(String.class, "Hola mundo " + i + "!")
                            .build());
                    Thread.sleep(1000);
                }
                // Mantener la conexión abierta enviando comentarios
                while (!session.isClosed()) {
                    OutboundSseEvent ping = sse.newEventBuilder()
                            .comment("keep-alive")          // envío de comentario SSE
                            .reconnectDelay(15000)          // instruye al cliente retry=15000 ms
                            .build();
                    session.send(ping);
                    Thread.sleep(15000);
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }).start();
    }
}
