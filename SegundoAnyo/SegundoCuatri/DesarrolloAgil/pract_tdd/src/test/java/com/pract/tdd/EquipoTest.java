package com.pract.tdd;

import static org.junit.jupiter.api.Assertions.assertThrows;

import org.junit.jupiter.api.Test;

public class EquipoTest {
    @Test
    public void ConstructorParametrizado_Excepciones() {
        assertThrows(IllegalArgumentException.class, () -> {
            new Equipo("", 0);
        });
    }
}
