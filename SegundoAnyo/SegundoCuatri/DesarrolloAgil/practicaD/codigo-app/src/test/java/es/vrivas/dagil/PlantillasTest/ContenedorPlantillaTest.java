package es.vrivas.dagil.PlantillasTest;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import es.vrivas.dagil.Plantillas.ContenedorPlantilla;
import es.vrivas.dagil.Plantillas.ContenidoPlantilla;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

/**
 * Clase de test para la clase Contenedor.
 */
public class ContenedorPlantillaTest {
    /**
     * Inicialización de los tests.
     */
    @BeforeAll
    public static void setUp() {
        System.out.println("Iniciando test clase Contenedor...");
    }

    // ---------------------------------------------------------------
    // Tests para el método add
    // ---------------------------------------------------------------

    /**
     * Excepción si se intenta añadir un objeto nulo.
     */
    @Test
    public void add_excepcion_si_objeto_nulo() {
        // Salta exepción si se intenta añadir un objeto nulo
        ContenedorPlantilla contenedor = new ContenedorPlantilla();
        try {
            contenedor.add(null);
            fail();
        } catch (IllegalArgumentException e) {
            System.err.println("Excepción lanzada: " + e.getMessage() + " para objeto nulo.");
        }

    }

    /**
     * Excepción si se intenta añadir un objeto que ya existe.
     */
    @Test
    public void add_excepcion_si_objeto_ya_existe() {
        try {
            ContenedorPlantilla contenedor = new ContenedorPlantilla();
            ContenidoPlantilla objeto = new ContenidoPlantilla()
                    .setDescripcion("add_excepcion_si_objeto_ya_existe")
                    .setId(1);
            contenedor.add(objeto);
            // Intento añadirlo otra vez: debería saltar la excepción.
            contenedor.add(objeto);
            fail();
        } catch (IllegalArgumentException e) {
            System.err.println("Excepción lanzada: " + e.getMessage() + " para objeto ya añadido.");
        }
    }

    /**
     * Excepción si se intenta añadir un objeto con un id que ya existe.
     */
    @Test
    public void add_excepcion_si_objeto_tiene_mismo_id_que_otro() {
        try {
            ContenedorPlantilla contenedor = new ContenedorPlantilla();
            contenedor
                    .add(new ContenidoPlantilla().setId(1).setDescripcion("Objeto 1"))
                    // Intento añadir un nuevo objeto con el mismo id
                    .add(new ContenidoPlantilla().setId(1).setDescripcion("Objeto 2"));
            fail();
        } catch (IllegalArgumentException e) {
            System.err.println("Excepción lanzada: " + e.getMessage() + " para objeto con id igual que otro.");
        }
    }

    /**
     * El método add devuelve el mismo objeto contenedor.
     */
    @Test
    public void add_devuelve_mismo_objeto() {
        // El método debe devolver el mismo objeto
        ContenedorPlantilla contenedor = new ContenedorPlantilla();
        ContenidoPlantilla objeto = new ContenidoPlantilla()
                .setDescripcion("Descripción en add_devuelve_mismo_objeto")
                .setId(1);
        assertSame(contenedor, contenedor.add(objeto));

    }

    /**
     * El método add inserta un objeto.
     */
    @Test
    public void add_inserta_objeto() {
        // El objeto se ha añadido al contenedor
        ContenidoPlantilla objeto = new ContenidoPlantilla()
                .setDescripcion("Descripción en add_inserta_objeto")
                .setId(1);
        ContenedorPlantilla contenedor = new ContenedorPlantilla()
                .add(objeto);
        assertTrue(contenedor.getPorId(1) != null);
        assertSame(contenedor.getPorId(1), objeto);
    }

    // ---------------------------------------------------------------
    // Tests para el método remove
    // ---------------------------------------------------------------

    /**
     * Excepción si se intenta eliminar un objeto nulo.
     */
    @Test
    public void remove_excepcion_si_objeto_nulo() {
        // Salta exepción si se intenta añadir un objeto nulo
        ContenedorPlantilla contenedor = new ContenedorPlantilla();
        try {
            contenedor.remove(null);
            contenedor.add(null);
            fail();
        } catch (IllegalArgumentException e) {
            System.err.println("Excepción lanzada: " + e.getMessage() + " para objeto nulo.");
        }

    }

    /**
     * Excepción si se intenta añadir un objeto que ya existe.
     */
    @Test
    public void remove_excepcion_si_objeto_no_existe() {
        try {
            ContenedorPlantilla contenedor = new ContenedorPlantilla();
            ContenidoPlantilla objeto = new ContenidoPlantilla()
                    .setDescripcion("remove_excepcion_si_objeto_no_existe")
                    .setId(1);
            contenedor.remove(objeto);
            fail();
        } catch (IllegalArgumentException e) {
            System.err.println("Excepción lanzada: " + e.getMessage() + " para objeto que no existía.");
        }
    }

    /**
     * El método remove devuelve el mismo objeto contenedor.
     */
    @Test
    public void remove_devuelve_mismo_objeto() {
        // El método debe devolver el mismo objeto
        ContenedorPlantilla contenedor = new ContenedorPlantilla();
        ContenidoPlantilla objeto = new ContenidoPlantilla()
                .setDescripcion("Descripción en remove_devuelve_mismo_objeto")
                .setId(1);
        contenedor.add(objeto);
        assertSame(contenedor, contenedor.remove(objeto));
    }

    /**
     * El método remove elimina un objeto.
     */
    @Test
    public void remove_elimina_objeto() {
        // El objeto se ha añadido al contenedor
        ContenidoPlantilla objeto = new ContenidoPlantilla()
                .setDescripcion("Descripción en remove_elimina_objeto")
                .setId(1);
        ContenedorPlantilla contenedor = new ContenedorPlantilla()
                .add(objeto);
        // Primero compruebo que lo ha añadido.
        assertSame(contenedor.getPorId(1), objeto);
        // Ahora compruebo que lo ha borrado
        contenedor.remove(objeto);
        assertTrue(contenedor.getPorId(objeto.getId()) == null);
    }
    
    // ---------------------------------------------------------------
    // Tests para el método getNumObjetosContenidos
    // ---------------------------------------------------------------
    
    /**
     * Un contenedor vacío devuelve 0 objetos contenidos.
     */
    @Test
    public void getNumObjetosContenidos_contenedor_vacio() {
        // Devuelve 0 si no hay objetos en el contenedor
        assert new ContenedorPlantilla().getNumObjetosContenidos() == 0;
    }

    /**
     * Un contenedor no vacío devuelve el número de objetos contenidos.
     */
    @Test
    public void getNumObjetosContenidos_contenedor_no_vacio() {
        // Creo un contenedor, le añado un contenido y compruebo que el número de objetos es 1
        ContenidoPlantilla objeto = new ContenidoPlantilla()
                .setDescripcion("Descripción en add_inserta_objeto")
                .setId(1);
        ContenedorPlantilla contenedor = new ContenedorPlantilla()
                .add(objeto);
        assert contenedor.getNumObjetosContenidos() == 1;
    }

    // ---------------------------------------------------------------
    // Tests para el método getPorPosicion
    // ---------------------------------------------------------------

    /**
     * Excepción si la posición es negativa.
     */
    @Test
    public void getPorPosicion_excepcion_posicion_negativa() {
        // Salta excepción si la posición no es válida
        // Prueba para posiciones menores que 0
        try {
            new ContenedorPlantilla().getPorPosicion(-1);
            fail();
        } catch (IllegalArgumentException e) {
            System.err.println("Excepción lanzada: " + e.getMessage() + " para posición -1.");
        }
    }

    /**
     * Excepción si la posición es mayor o igual al número de elementos que hay.
     */
    @Test
    public void getPorPosicion_excepcion_posicion_superior_existentes() {
        try {
            new ContenedorPlantilla().getPorPosicion(0);
            fail();
        } catch (IllegalArgumentException e) {
            System.err.println("Excepción lanzada: " + e.getMessage() + " para posición 0.");
        }
        try {
            new ContenedorPlantilla().getPorPosicion(1);
            fail();
        } catch (IllegalArgumentException e) {
            System.err.println("Excepción lanzada: " + e.getMessage() + " para posición 1.");
        }
    }

    /**
     * Prueba de valores límite para el método getPorPosicion.
     */
    @Test
    public void getPorPosicion_valores_limite() {
        ContenidoPlantilla objeto0 = new ContenidoPlantilla()
                .setDescripcion("Descripción en testGetPorPosicion para objeto0")
                .setId(0);
        ContenidoPlantilla objeto1 = new ContenidoPlantilla()
                .setDescripcion("Descripción en testGetPorPosicion para objeto1")
                .setId(1);
        ContenedorPlantilla contenedor = new ContenedorPlantilla()
                .add(objeto0)
                .add(objeto1);
        assert contenedor.getPorPosicion(0) != null;
        assertSame(contenedor.getPorPosicion(0), objeto0);

        assert contenedor.getPorPosicion(1) != null;
        assertSame(contenedor.getPorPosicion(1), objeto1);
    }

    // ---------------------------------------------------------------
    // Tests para el método getPorId
    // ---------------------------------------------------------------

    /**
     * Prueba para un contenedor vacío.
     */
    @Test
    public void getPorId_contenedor_vacio() {
        assert new ContenedorPlantilla().getPorId(1) == null;
    }

    /**
     * Prueba para un contenedor con elementos.
     */
    @Test
    public void getPorId_contenedor_con_elementos() {
        // Devuelve el objeto si está en el contenedor
        ContenidoPlantilla objeto = new ContenidoPlantilla()
                .setDescripcion("Descripción en testGetPorId")
                .setId(1);
        ContenedorPlantilla contenedor = new ContenedorPlantilla().add(objeto);
        assert contenedor.getPorId(1) != null;
        assertSame(contenedor.getPorId(1), objeto);
    }

    // ---------------------------------------------------------------
    // Tests para el método toString
    // ---------------------------------------------------------------

    /**
     * toString devuelve [] si no hay objetos en el contenedor.
     */
    @Test
    public void toString_contenedor_vacio() {
        assertEquals("[]", new ContenedorPlantilla().toString());
    }

    /**
     * toString devuelve un string con los objetos en formato JSON.
     */
    @Test
    public void toString_contenedor_no_vacio() {
        ContenedorPlantilla contenedor = new ContenedorPlantilla();
        ContenidoPlantilla objeto1 = new ContenidoPlantilla()
                .setDescripcion("Descripción en toString_contenedor_no_vacio para objeto1")
                .setId(1);
        contenedor.add(objeto1);
        // Para un solo objeto
        assertEquals("[\n{id: 1, descripcion: 'Descripción en toString_contenedor_no_vacio para objeto1'},\n]",
                contenedor.toString());
        ContenidoPlantilla objeto2 = new ContenidoPlantilla()
                .setDescripcion("Descripción en toString_contenedor_no_vacio para objeto2")
                .setId(2);
        contenedor.add(objeto2);
        // Para dos objetos
        String cadenaJSONEsperada = "[\n"
                + "{id: 1, descripcion: 'Descripción en toString_contenedor_no_vacio para objeto1'},\n"
                + "{id: 2, descripcion: 'Descripción en toString_contenedor_no_vacio para objeto2'},\n"
                + "]";
        assertEquals(cadenaJSONEsperada, contenedor.toString());

    }

    /**
     * Finalización de los tests.
     */
    @AfterAll
    public static void tearDown() {
        System.out.println("Finalizando test clase Contenedor...");
    }

}
