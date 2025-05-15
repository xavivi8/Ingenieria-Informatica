package org.vaadin.example.excepciones;

public class NumeroDePlazasIncorrecto extends RuntimeException {
    public NumeroDePlazasIncorrecto(String message) {
        super(message);
    }
    public NumeroDePlazasIncorrecto(){}
}
