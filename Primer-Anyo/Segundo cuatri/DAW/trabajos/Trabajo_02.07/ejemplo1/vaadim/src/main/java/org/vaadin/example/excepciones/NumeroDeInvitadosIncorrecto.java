package org.vaadin.example.excepciones;

public class NumeroDeInvitadosIncorrecto extends RuntimeException {
    public NumeroDeInvitadosIncorrecto(String message) {
        super(message);
    }
    public NumeroDeInvitadosIncorrecto(){}
}
