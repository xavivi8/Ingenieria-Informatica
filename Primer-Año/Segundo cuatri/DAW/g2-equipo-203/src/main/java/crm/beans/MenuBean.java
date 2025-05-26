package crm.beans;

import jakarta.enterprise.context.SessionScoped;
import jakarta.inject.Named;
import java.io.Serializable;

@Named
@SessionScoped
public class MenuBean implements Serializable {
    private String vistaActual = "/pages/home.xhtml"; // Página inicial por defecto

    // Getter y setter para la vista actual
    public String getVistaActual() {
        return vistaActual;
    }

    public void cambiarVista(String vista) {
        // Cambia la vista según el enlace seleccionado
        this.vistaActual = "/pages/" + vista + ".xhtml";
    }
}
