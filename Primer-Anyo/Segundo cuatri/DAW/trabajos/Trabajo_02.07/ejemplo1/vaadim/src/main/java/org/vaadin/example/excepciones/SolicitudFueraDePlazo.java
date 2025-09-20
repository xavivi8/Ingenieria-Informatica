package org.vaadin.example.excepciones;

public class SolicitudFueraDePlazo extends RuntimeException {
    public SolicitudFueraDePlazo(String message) {
        super(message);
    }
    public SolicitudFueraDePlazo(){}
}
