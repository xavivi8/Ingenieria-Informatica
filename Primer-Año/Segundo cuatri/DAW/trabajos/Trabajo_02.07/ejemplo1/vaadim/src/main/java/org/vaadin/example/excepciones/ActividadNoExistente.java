package org.vaadin.example.excepciones;

public class ActividadNoExistente extends RuntimeException {
    public ActividadNoExistente(String message) {
        super(message);
    }
    public ActividadNoExistente(){}
}
