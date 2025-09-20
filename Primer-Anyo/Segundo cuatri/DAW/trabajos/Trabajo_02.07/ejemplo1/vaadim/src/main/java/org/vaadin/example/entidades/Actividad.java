package org.vaadin.example.entidades;



import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Positive;
import jakarta.validation.constraints.PositiveOrZero;
import lombok.Getter;
import lombok.Setter;
import org.vaadin.example.excepciones.FechaIncorrecta;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Actividad {
    @Getter @Setter
    private int id;

    @Getter @Setter @NotBlank
    private String titulo;

    @Getter @Setter
    private String descripcion;

    @Getter @Setter @PositiveOrZero
    private float precio;

    @Getter @Setter @Positive
    private int plazas;

    @Getter @Setter @NotNull
    private LocalDate fechaCelebracion;

    @Getter @Setter @NotNull
    private LocalDate fechaInicioInscripcion;

    @Getter @Setter @NotNull
    private LocalDate fechaFinInscripcion;

    @Getter
    private int plazasAsignadas;
    private boolean sociosAsignados;

    @Getter @Setter
    private String imagen = "0.jpeg";

    private List<Socio> solicitudes;

    private static int idCreador = 0;

    public Actividad() {}

    public Actividad(@NotBlank String titulo, String descripcion, @PositiveOrZero float precio, @Positive int plazas,@NotBlank LocalDate fechaCelebracion,@NotBlank LocalDate fechaInicioInscripcion,@NotBlank LocalDate fechaFinInscripcion) {
        if(fechaInicioInscripcion.isAfter(fechaFinInscripcion) || fechaInicioInscripcion.isAfter(fechaCelebracion) || fechaFinInscripcion.isAfter(fechaCelebracion)){
            throw new FechaIncorrecta();
        }else {
            this.titulo = titulo;
            this.descripcion = descripcion;
            this.precio = precio;
            this.plazas = plazas;
            this.fechaCelebracion = fechaCelebracion;
            this.fechaInicioInscripcion = fechaInicioInscripcion;
            this.fechaFinInscripcion = fechaFinInscripcion;
            this.solicitudes = new ArrayList<>();
            plazasAsignadas = 0;
            sociosAsignados = false;
            this.id = idCreador++;
            this.imagen = "0.jpeg";
        }
    }

    public Actividad( String titulo, String descripcion, float precio, int plazas, LocalDate fechaCelebracion, LocalDate fechaInicioInscripcion, LocalDate fechaFinInscripcion, String imagen) {
        this.id = idCreador++;
        this.titulo = titulo;
        this.descripcion = descripcion;
        this.precio = precio;
        this.plazas = plazas;
        this.fechaCelebracion = fechaCelebracion;
        this.fechaInicioInscripcion = fechaInicioInscripcion;
        this.fechaFinInscripcion = fechaFinInscripcion;
        this.imagen = imagen;
        plazasAsignadas = 0;
        sociosAsignados = false;
    }



    /**
     * Añade una nueva solicitud a la actividad, si el socio ha pagado y hay hueco se le asigna directamente la plaza
     */
    public void addSolicitud(Socio solicitud) {
        solicitudes.add(solicitud);

    }

    /**
     * Borra una solicitud del conjunto de solicitudes de la actividad
     */
    public void deleteSolicitud(Socio solicitud) {
        solicitudes.remove(solicitud);
    }

    public List<Socio> getSolicitudes(){return solicitudes;}

    public int nSolicitudes(){return solicitudes.size();}
}
