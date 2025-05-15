package org.vaadin.example.views;

import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.button.ButtonVariant;
import com.vaadin.flow.component.formlayout.FormLayout;
import com.vaadin.flow.component.grid.Grid;
import com.vaadin.flow.component.html.H3;
import com.vaadin.flow.component.notification.Notification;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.component.textfield.TextField;
import com.vaadin.flow.data.binder.BeanValidationBinder;
import com.vaadin.flow.data.binder.BinderValidationStatus;
import com.vaadin.flow.data.binder.ValidationException;
import com.vaadin.flow.router.Route;
import com.vaadin.flow.router.RouterLink;
import org.springframework.beans.factory.annotation.Autowired;
import org.vaadin.example.ServiciosAdmin;
import org.vaadin.example.entidades.Socio;
import com.vaadin.flow.component.UI; // para navegación
import org.vaadin.example.layouts.MainLayout;

@Route(value = "", layout = MainLayout.class)
public class MainView extends HorizontalLayout {

    private final ServiciosAdmin service;

    // Campos del formulario (nombrados según propiedades de Socio)
    private final TextField email = new TextField("Email");
    private final TextField nombre = new TextField("Nombre");
    private final TextField apellidos = new TextField("Apellidos");
    private final TextField telefono = new TextField("Teléfono");
    private final TextField claveAcceso = new TextField("Clave Acceso");
    private final Button saveButton = new Button("Guardar");

    // Binder con Bean Validation
    private final BeanValidationBinder<Socio> binder = new BeanValidationBinder<>(Socio.class);
    private Socio currentSocio;

    // Grid de socios
    private final Grid<Socio> grid = new Grid<>(Socio.class, false);

    @Autowired
    public MainView(ServiciosAdmin service) {

        this.service = service;
        this.currentSocio = new Socio();

        setSizeFull();

        // PANEL IZQUIERDO: formulario
        VerticalLayout formWrapper = new VerticalLayout();
        formWrapper.setWidth("30%");
        formWrapper.add(new H3("Formulario Socio"));

        FormLayout form = new FormLayout();
        form.add(email, nombre, apellidos, telefono, claveAcceso, saveButton);

        binder.bindInstanceFields(this);

        // Botón Guardar con validación
        saveButton.addClickListener(e -> {
            BinderValidationStatus<Socio> status = binder.validate();
            if (status.hasErrors()) {
                status.getValidationErrors().forEach(err ->
                        Notification.show(err.getErrorMessage())
                );
                return;
            }
            try {
                binder.writeBean(currentSocio);
                if (currentSocio.getIdSocio() == 0 ||
                        service.getAllSocios().stream()
                                .noneMatch(s -> s.getIdSocio() == currentSocio.getIdSocio())) {
                    service.crearSocio(currentSocio);
                    Notification.show("Socio añadido");
                } else {
                    service.actualizarSocio(currentSocio);
                    Notification.show("Socio actualizado");
                }
                // Reset formulario
                currentSocio = new Socio();
                binder.readBean(currentSocio);
                updateGrid();
            } catch (ValidationException ex) {
                Notification.show("Error de validación: " + ex.getMessage());
            }
        });

        // Inicializar formulario vacío
        binder.readBean(currentSocio);
        formWrapper.add(form);


        // PANEL DERECHO: grid
        VerticalLayout gridWrapper = new VerticalLayout();
        gridWrapper.setWidth("70%");
        gridWrapper.setSizeFull();
        gridWrapper.add(new H3("Lista de Socios"));

        grid.addColumn(Socio::getIdSocio).setHeader("ID").setAutoWidth(true);
        grid.addColumn(Socio::getEmail).setHeader("Email").setAutoWidth(true);
        grid.addColumn(Socio::getNombre).setHeader("Nombre").setAutoWidth(true);
        grid.addColumn(Socio::getApellidos).setHeader("Apellidos").setAutoWidth(true);
        grid.addColumn(Socio::getTelefono).setHeader("Teléfono").setAutoWidth(true);
        grid.addColumn(Socio::isHaPagado).setHeader("Ha pagado").setAutoWidth(true);

        grid.addComponentColumn(socio -> {
            Button edit = new Button("Editar");
            edit.addClickListener(ev -> {
                currentSocio = socio;
                binder.readBean(currentSocio);
            });

            Button delete = new Button("Borrar");
            delete.addThemeVariants(ButtonVariant.LUMO_ERROR);
            delete.addClickListener(ev -> {
                service.borrarSocio(socio.getIdSocio());
                Notification.show("Socio eliminado");
                updateGrid();
            });

            HorizontalLayout actions = new HorizontalLayout(edit, delete);
            return actions;
        }).setHeader("Acciones").setAutoWidth(true);

        grid.setSizeFull();
        gridWrapper.add(grid);

        add(formWrapper, gridWrapper);

        updateGrid();
    }

    private void updateGrid() {
        grid.setItems(service.getAllSocios());
    }
}
