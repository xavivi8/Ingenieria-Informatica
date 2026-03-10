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
}
