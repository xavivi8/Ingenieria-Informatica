# 01.03 Uso del API HTML5 Server-Side Events entre javascript y JakartaEE 10

##  Autores

* Pablo Mediano Martínez  (@pablomediano)
* María Lucía Gómez Gutiérrez  (@mlgg0019)
* Mario Martínez Gallego (@mmg00226)

## Descripción breve

Este sistema usa **Server-Sent Events (SSE)** para enviar notificaciones en tiempo real del servidor al navegador. Cuando el cliente abre una conexión con `EventSource`, el servidor registra esa conexión (`SseEventSink`) y la asocia al usuario conectado.

Cada vez que ocurre un evento relevante, el servidor crea un mensaje (`OutboundSseEvent`) y lo envía por esa conexión al navegador, que lo muestra dinámicamente sin necesidad de recargar la página. Es un mecanismo simple, eficiente y unidireccional para mantener actualizados a los usuarios en tiempo real.

## Bibliografía y referencias

-   [Uso de eventos enviados por el servidor](https://developer.mozilla.org/en-US/docs/Web/API/Server-sent_events/Using_server-sent_events)
    
-   [Interfaz EventSource](https://developer.mozilla.org/en-US/docs/Web/API/EventSource)
    
-   [Idea general de Server Sent Events](https://gabrielchavez.me/que-es-server-sent-events-sse/#%C2%BFQue_es_Server_Sent_Events)
    
-   [Comparación e implementación SSE](https://medium.com/@atarax/server-side-events-sse-a-deep-dive-into-client-server-architecture-implementation-in-golang-cc15628605fd)
    
-   [WebSockets vs SSE](https://ably.com/concepts/websockets-vs-sse)
    
-   [HTML5 SSE](https://www.html5rocks.com/en/tutorials/eventsource/basics/)
    
-   [SSE Events Interfaz](https://jakarta.ee/specifications/platform/10/apidocs/jakarta/ws/rs/sse/sseevent)
    
-   [SSE JAX-RS](https://www.baeldung.com/java-ee-jax-rs-sse)
    
-   [Server to a Client in Jakarta EE Servlet](https://www.demo2s.com/g/java/how-to-push-resources-from-a-server-to-a-client-in-jakarta-ee-servlet.html)

## Inteligencias Artificales Generativas empleadas

-   Chat Gpt: Generación de código, búsqueda de fuentes
    
-   Gemini : Investigación profunda acerca de limitaciones de SSE, búsqueda de imágenes
    
-   Deep Seek: Afianzamiento de conceptos, comprobación de fuentes.

## Materiales complementarios

En el ejemplo 1 realizamos un código simple en el que el cliente inicia una conexión con el servidor y el servidor le envía al cliente 10 mensajes de Hola mundo que se muestran en la vista.

En el ejemplo 2 hemos adaptado el uso de SSE a nuestro proyecto de prácticas, una página web de intercambio de libros, en la cual puedes registrar libros para intercambiar, para en el que tu inicias sesión con dos usuarios, en una ventana cada uno, y cuando un usuario registra un libro se envía una notificación de que el usuario X ha registrado el libro Y al resto de usuarios, dicha notificación aparece en la vista home, la pantalla de inicio.
