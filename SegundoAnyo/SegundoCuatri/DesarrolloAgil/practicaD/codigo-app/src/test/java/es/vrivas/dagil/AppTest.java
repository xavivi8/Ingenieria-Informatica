package es.vrivas.dagil;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

/**
 * Tests de la clase principal App.
 */
class AppTest {
    /**
     * Inicialización de los tests.
     */
    @BeforeAll
    public static void setUp() {
        System.out.println("Iniciando test clase App...");
    }

    /**
     * Test de introducción de un conjunto de datos de prueba.
     */
    @Test
    public void testIntroducir_datos_de_prueba() {
        assertEquals(App.MAX_OBJETOS_PRUEBA, App.establecer_datos_de_prueba());
    }

    /**
     * Finalización de los tests.
     */
    @AfterAll
    public static void tearDown() {
        System.out.println("Finalizando test clase App...");
    }
}
