package org.vaadin.example.excepciones;

public class UsuarioNoRegistrado extends RuntimeException {
    public UsuarioNoRegistrado(String message) {
        super(message);
    }
    public UsuarioNoRegistrado(){}
}
