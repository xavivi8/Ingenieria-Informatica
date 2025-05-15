package org.vaadin.example.excepciones;

public class ActividadYaCreada extends RuntimeException {
    public ActividadYaCreada(String message) {
        super(message);
    }
    public ActividadYaCreada(){}
}
