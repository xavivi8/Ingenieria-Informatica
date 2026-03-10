package com.pract.tdd;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;

public class EquipoTest {
    @Test
    public void ConstructorParametrizado_Excepciones() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Equipo("", 0);
        });
        assertThrows(IllegalArgumentException.class, () -> {
            new Equipo(null, 0);
        });
    }

    @Test
    public void ConstructorParametrizado() {
        assertEquals("Equipo 1", new Equipo("Equipo 1", 0).getNombre());
        assertEquals(22, new Equipo("Equipo 1", 22).getPuntos());
    }

    @Test
    void getNombre() {
        assertEquals("Equipo 1", new Equipo("Equipo 1", 0).getNombre());
    }

    @Test
    void getPuntos() {
        assertEquals(78, new Equipo("Equipo 1", 78).getPuntos());
    }
}
