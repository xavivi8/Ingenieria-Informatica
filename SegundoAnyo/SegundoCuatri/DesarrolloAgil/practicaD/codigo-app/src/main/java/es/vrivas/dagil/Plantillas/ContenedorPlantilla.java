package es.vrivas.dagil.Plantillas;

import java.util.ArrayList;

import es.vrivas.dagil.ContenedorInterface;

/**
 * Clase Contenedor.
 * Representa un contenedor de objetos de la clase Contenido.
 */
public class ContenedorPlantilla implements ContenedorInterface<ContenidoPlantilla> {

    /// ArrayList con el conjunto de objetos contenidos.
    private ArrayList<ContenidoPlantilla> objetosContenidos;

    /**
     * Constructor.
     */
    public ContenedorPlantilla() {
        objetosContenidos = new ArrayList<ContenidoPlantilla>();
    }

    /**
     * Devuelve el número de objetos que hay en el contenedor.
     * @return Número de objetos contenidos en el contenedor.
     */
    public int getNumObjetosContenidos() {
        return objetosContenidos.size();
    }

    /**
     * Devuelve el objeto que que hay en la posición indicada.
     * @param posicion Posición del objeto a devolver.
     * @return El objeto que hay en la posición indicada.
     * @exception IllegalArgumentException Si la posición no es válida.
     */
    public ContenidoPlantilla getPorPosicion(final int posicion) throws IllegalArgumentException {
        if (posicion < 0 || posicion >= objetosContenidos.size()) {
            throw new IllegalArgumentException(
                    "La posición debe estar entre 0 y " + (objetosContenidos.size() - 1));
        }
        return objetosContenidos.get(posicion);
    }

    /**
     * Devuelve el objeto que tiene el id indicado.
     * @param id Id del objeto a devolver.
     * @return El objeto que tiene el id indicado o null si no existe.
    */
    public ContenidoPlantilla getPorId(final int id) {
        ContenidoPlantilla objeto = null;
        for (int i = 0; objeto == null && i < objetosContenidos.size(); ++i) {
            if (objetosContenidos.get(i).getId() == id) {
                objeto = objetosContenidos.get(i);
            }
        }
        return objeto;
    }

    /**
     * Devuelve el conjunto de objetos que hay en el contenedor en forma de string.
     * @return Cadena con el conjunto de objetos que hay en el contenedor en formato JSON.
     */
    public final String toString() {
        String cadenaFinal = "[";
        for (int i = 0; i < objetosContenidos.size(); i++) {
            cadenaFinal += (i == 0 ? "\n" : "") + objetosContenidos.get(i).toString() + ",\n";
        }
        cadenaFinal += "]";
        return cadenaFinal;
    }

    /**
     * Añade un objeto al contenedor.
     * @param objeto Objeto a añadir.
     * @exception IllegalArgumentException Si el objeto ya está en el contenedor.
     * @exception IllegalArgumentException Si ya hay un objeto con el mismo id en el contenedor.
     * @exception IllegalArgumentException Si el objeto es NULL.
     * @return La propia instancia de Contenedor.
     */
    public ContenedorPlantilla add(final ContenidoPlantilla objeto) throws IllegalArgumentException {
        if (objeto == null) {
            throw new IllegalArgumentException("El objeto que se intenta añadir es NULL");
        }
        if (objetosContenidos.contains(objeto)) {
            throw new IllegalArgumentException("El objeto ya está en el contenedor");
        }
        if (getPorId(objeto.getId()) != null) {
            throw new IllegalArgumentException("Ya hay un objeto con el mismo id en el contenedor");
        }
        objetosContenidos.add(objeto);
        return this;
    }

    /**
     * Elimina un objeto del contenedor.
     * @param objeto Objeto a eliminar del contenedor.
     * @exception IllegalArgumentException Si el objeto no está en el contenedor.
     * @exception IllegalArgumentException Si el objeto es NULL.
     * @return La propia instancia de Contenedor.
     */
    public ContenedorPlantilla remove(final ContenidoPlantilla objeto) throws IllegalArgumentException {
        if (objeto == null) {
            throw new IllegalArgumentException("Contenedor: remove: El objeto que se intenta eliminar es NULL");
        }
        if (!objetosContenidos.contains(objeto)) {
            throw new IllegalArgumentException("Contenedor: remove: El objeto no está en el contenedor");
        }
        objetosContenidos.remove(objeto);
        return this;
    }
}
