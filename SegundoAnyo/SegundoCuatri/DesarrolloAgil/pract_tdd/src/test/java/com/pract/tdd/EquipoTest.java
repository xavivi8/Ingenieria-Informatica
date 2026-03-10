package com.pract.tdd;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

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

    @Test
    void comparaPorPuntosInverso() {
        Equipo e1 = new Equipo("A", 30);
        Equipo e2 = new Equipo("B", 45);
        assertTrue(e1.comparaPorPuntosInverso(e2) > 0);
        assertTrue(e2.comparaPorPuntosInverso(e1) < 0);
        Equipo e3 = new Equipo("C", 45);
        assertTrue(e2.comparaPorPuntosInverso(e3) == 0);
    }

    @Test
    public void setNombre_excepciones() {
        Equipo e1 = new Equipo("A", 32);

        assertThrows(IllegalArgumentException.class, () -> {
            e1.setNombre("");
        });

        assertThrows(IllegalArgumentException.class, () -> {
            e1.setNombre(null);
        });
    }

    @Test
    public void setNombre() {
        Equipo e1 = new Equipo("A", 32);
        e1.setNombre("B");
        assertEquals("B", e1.getNombre());
        assertSame(e1, e1.setNombre("G"));
    }
}
