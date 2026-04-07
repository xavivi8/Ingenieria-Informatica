/**
 * Aplicación para usar las clases Contenedor y Contenido de forma genérica
 * @author Víctor Rivas <vrivas@ujaen.es>
 * @date 10-mar-2026
 */

package es.vrivas.dagil;

import es.vrivas.dagil.Plantillas.ContenedorPlantilla;
import es.vrivas.dagil.Plantillas.ContenidoPlantilla;

/**
 * Clase principal de la aplicación.
 */
public final class App {
    /**
     * Título de la aplicación.
     */
    public static final String TITULO = "Clases Contenedor y Contenido";

    /**
     * Autor/a de la aplicación.
     */
    public static final String AUTOR = "Víctor Rivas <vrivas@ujaen.es>";

    /**
    *  Máximo número de objetos de prueba.
    */
    public static final int MAX_OBJETOS_PRUEBA = 6;

    /// Un objeto contenedor.
    private static ContenedorPlantilla contenedor = new ContenedorPlantilla();

    /// Número de líneas de separación entre el menú y el texto superior.
    private static final int LINEAS_SEPARACION_MENU = 5;

    /// Constructor privado para evitar instanciación.
    private App() {
    }

    /**
    * Método para introducir algunos datos de prueba en el contenedor.
    */
    public static int establecer_datos_de_prueba() {
        for (int i = 0; i < MAX_OBJETOS_PRUEBA; ++i) {
            contenedor.add(new ContenidoPlantilla().setId(i).setDescripcion("Objeto " + i));
        }
        return contenedor.getNumObjetosContenidos();
    }

    /**
     * Método para responder a la opción 1 del menú: mostrar contenido del objeto contenedor.
     */
    public static void mostrar_contenido_del_objeto_contenedor() {
        System.out.println("Opción 1: Mostrar contenido del objeto contenedor");
        System.out.println(contenedor.toString());
    }

    /**
     * Método para mostrar el menú principal y leer la opción elegida.
     * @return Opción elegida por el usuario.
     */
    public static int menu_principal() {
        System.out.println("**** MENU ****");
        System.out.println("     ----");
        System.out.println("1. Mostrar contenido del objeto contenedor");
        System.out.println("     ----");
        System.out.println("0. Terminar");
        System.out.println("--------------------");
        System.out.print("Introduzca una opción: ");
        String entrada = System.console().readLine();
        System.out.println();

        return Integer.parseInt(entrada);
    }

    /**
     * Método para pausar la ejecución hasta que el usuario pulse una tecla.
     */
    private static void pausa() {
        System.out.println("(Pulse una tecla para continuar...)");
        System.console().readLine();
    }

    /**
    * Método para separar el menú del texto superior.
    */
    private static void separacionMenu(final int numLineas) {
        for (int i = 0; i < numLineas; ++i) {
            System.out.println();
        }
    }

    /**
     * Función principal.
     * @param args Argumentos de la línea de comandos.
     */
    public static void main(String[] args) {
        System.out.println("\n" + TITULO + "    (por " + AUTOR + ")");
        establecer_datos_de_prueba();
        boolean salir = false;
        separacionMenu(LINEAS_SEPARACION_MENU);
        do {
            switch (menu_principal()) {
                case 0:
                    salir = true;
                    break;
                case 1:
                    mostrar_contenido_del_objeto_contenedor();
                    pausa();
                    break;
                default:
                    System.out.println("Opción no válida");
            }

        } while (!salir);
        System.out.println("Fin de la aplicación.");
    }
}
