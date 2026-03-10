package com.pract.tdd;

import java.util.ArrayList;

/**
 * Hello world!
 */
public final class App {
    private App() {
    }

    /// Equipos que forman mi liga
    static ArrayList<Equipo> misEquipos = new ArrayList<Equipo>();

    /**
     * Muestra en pantalla el listado de equipos, ordenado por los puntos que tienen.
     */
    final protected static void imprimeClasificacion() {
        System.out.println("Clasificación:");
        System.out.println("=============");

        for (int i = 0; i < misEquipos.size(); ++i) {
            System.out.println((i + 1) +
                            ". " +
                            misEquipos.get(i).getNombre() +
                            "-" +
                            misEquipos.get(i).getPuntos());
        }
    }

    /**
     * Says hello to the world.
     * @param args The arguments of the program.
     */
    public static void main(String[] args) {
        System.out.println("Hello World!");
    }
}
