package com.pract.tdd;

public class Equipo {
    /// Nombre del equipo
    String nombre;

    /// Puntos del equipo
    int puntos;

    /**
     * Constructor parametrizado.
     * @param unNombre
     * @param unosPuntos
     * @throws IllegalArgumentException unNombre no puede ser vacío.
     */
    public Equipo(final String unNombre, final int unosPuntos) {
        if (unNombre == null || unNombre == "")
            throw (new IllegalArgumentException(
                "Equipo: Ctor. parametrizado: Nombre no puede ser null ni cadena vacía."));
        this.nombre = unNombre;
        this.puntos = unosPuntos;
    }

    /**
     * Compara dos equipos considerando que el que tiene más puntos se coloca antes que el que tiene
     * menos puntos.
     * @param otroEquipo Equipo con el que voy a comparar a this.
     * @return Un número negativo si this tiene más puntos que otroEquipo; un número positivo si this
     * tiene menos puntos que otroEquipo; y 0, si tienen los mismos puntos.
     */
    final public int comparaPorPuntosInverso(final Equipo otroEquipo) {
        if (this.puntos > otroEquipo.puntos)
            return -1;
        if (this.puntos < otroEquipo.puntos)
            return 1;
        return 0;
    }

    /**
     * Devuelve el nombre del equipo
     * @return El nombre del equipo.
     */
    final public String getNombre() {
        return this.nombre;
    }

    /**
     * Devuelve los puntos del equipo
     * @return Los puntos del equipo.
     */
    final public int getPuntos() {
        return this.puntos;
    }

    /**
     * Establece un nuevo nombre para el equipo.
     * @param unNombre El nuevo nombre para el equipo.
     * @throws IllegalArgumentException unNombre no puede ser vacío.
     * @throws IllegalArgumentException unNombre no puede ser null.
     * @post Modifica el nombre del equipo.
     * @return El propio objeto para encadenar llamadas.
     */
    public Equipo setNombre(final String unNombre) {
        if (unNombre == null || unNombre == "")
            throw (new IllegalArgumentException(
                "Equipo: setNombre: Nombre no puede ser null ni cadena vacía."));
        this.nombre = unNombre;
        return this;
    }
}
