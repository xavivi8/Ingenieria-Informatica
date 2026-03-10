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
}
