/**
 * Interface para las clases contenedoras.
 * @author Víctor Rivas <vrivas@ujaen.es>
 * @date 10-mar-2026
*/

package es.vrivas.dagil;

/**
 * Interface para las clases contenedoras.
 * @param <T_Contenido> El tipo de los objetos que se van a almacenar en el contenedor.
 */
public interface ContenedorInterface<T_Contenido> {
    /**
     * Devuelve el número de objetos que hay en el contenedor.
     * @return Número de objetos contenidos en el contenedor.
     */
    int getNumObjetosContenidos();

    /**
     * Devuelve el objeto que que hay en la posición indicada.
     * @param posicion Posición del objeto a devolver.
     * @return El objeto que hay en la posición indicada.
     * @exception IllegalArgumentException Si la posición no es válida.
     */
    T_Contenido getPorPosicion(int posicion) throws IllegalArgumentException;

    /**
     * Devuelve el objeto que tiene el id indicado.
     * @param id Id del objeto a devolver.
     * @return El objeto que tiene el id indicado o null si no existe.
    */
    T_Contenido getPorId(int id);

    /**
     * Devuelve el conjunto de objetos que hay en el contenedor en forma de string.
     * @return Cadena con el conjunto de objetos que hay en el contenedor en formato JSON.
     */
    String toString();

    /**
     * Añade un objeto al contenedor.
     * @param objeto Objeto a añadir.
     * @exception IllegalArgumentException Si el objeto ya está en el contenedor.
     * @exception IllegalArgumentException Si ya hay un objeto con el mismo id en el contenedor.
     * @exception IllegalArgumentException Si el objeto es NULL.
     * @return La propia instancia de Contenedor.
     */
    ContenedorInterface<T_Contenido> add(T_Contenido objeto) throws IllegalArgumentException;

    /**
     * Elimina un objeto del contenedor.
     * @param objeto Objeto a eliminar del contenedor.
     * @exception IllegalArgumentException Si el objeto no está en el contenedor.
     * @exception IllegalArgumentException Si el objeto es NULL.
     * @return La propia instancia de Contenedor.
     */
    ContenedorInterface<T_Contenido> remove(T_Contenido objeto) throws IllegalArgumentException;
}

