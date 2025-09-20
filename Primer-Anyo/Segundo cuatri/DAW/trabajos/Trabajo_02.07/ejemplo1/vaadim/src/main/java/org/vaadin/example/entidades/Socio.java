package org.vaadin.example.entidades;

import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Pattern;
import lombok.*;

@Getter
@Setter
@ToString
public class Socio {
    private int idSocio;
    @Email
    private String email;
    @NotBlank
    private String nombre;
    @NotBlank
    private String apellidos;
    @Pattern(regexp="^(\\+34|0034|34)?[6789]\\d{8}$",
            message = "el teléfono tiene que ser un número válido")
    private String telefono;
    @NotBlank
    private String claveAcceso;
    private boolean haPagado;

    private static int id = 0;

    public Socio(@NotBlank @Email String email, @NotBlank String nombre, @NotBlank String apellidos,
                 @Pattern(regexp="^(\\+34|0034|34)?[6789]\\d{8}$") String telefono, @NotBlank String claveAcceso) {
        this.email = email;
        this.nombre = nombre;
        this.apellidos = apellidos;
        this.telefono = telefono;
        this.claveAcceso = claveAcceso;
        this.haPagado = false;
        this.idSocio = id++;
    }

    public Socio(int idSocio, String email, String nombre, String apellidos, String telefono, String claveAcceso, boolean haPagado) {
        this.idSocio = idSocio;
        this.email = email;
        this.nombre = nombre;
        this.apellidos = apellidos;
        this.telefono = telefono;
        this.claveAcceso = claveAcceso;
        this.haPagado = haPagado;
    }

    public Socio() {
        this.idSocio = id++;
    }


}
