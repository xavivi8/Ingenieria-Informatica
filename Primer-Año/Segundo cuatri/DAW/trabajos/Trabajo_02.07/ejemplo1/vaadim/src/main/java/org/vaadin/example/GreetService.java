package org.vaadin.example;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import org.springframework.stereotype.Service;
import org.vaadin.example.entidades.Socio;

@Service
public class GreetService implements Serializable {

    private final List<Socio> socios;

    public GreetService() {
        this.socios = new ArrayList<>();
    }

    public void addSocio(Socio socio) {
        socios.add(socio);
    }

    public void removeSocio(Socio socio) {
        socios.remove(socio);
    }

    /** Devuelve una copia de la lista actual de Socios */
    public List<Socio> getAllSocios() {
        return new ArrayList<>(socios);
    }

    public String greet(String name) {
        if (name == null || name.isEmpty()) {
            return "Hello anonymous user";
        } else {
            return "Hello " + name;
        }
    }
}
