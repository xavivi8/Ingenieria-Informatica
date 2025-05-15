package org.vaadin.example.views;

import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.button.ButtonVariant;
import com.vaadin.flow.component.datepicker.DatePicker;
import com.vaadin.flow.component.formlayout.FormLayout;
import com.vaadin.flow.component.grid.Grid;
import com.vaadin.flow.component.html.H3;
import com.vaadin.flow.component.notification.Notification;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.component.textfield.NumberField;
import com.vaadin.flow.component.textfield.TextArea;
import com.vaadin.flow.component.textfield.TextField;
import com.vaadin.flow.data.binder.BeanValidationBinder;
import com.vaadin.flow.data.binder.BinderValidationStatus;
import com.vaadin.flow.data.binder.ValidationException;
import com.vaadin.flow.router.Route;
import org.springframework.beans.factory.annotation.Autowired;
import org.vaadin.example.ServiciosAdmin;
import org.vaadin.example.entidades.Actividad;
import org.vaadin.example.excepciones.FechaIncorrecta;
import org.vaadin.example.layouts.MainLayout;

@Route(value = "actividades", layout = MainLayout.class)
public class ActividadesView extends HorizontalLayout {

    private final ServiciosAdmin service;
    private final BeanValidationBinder<Actividad> binder = new BeanValidationBinder<>(Actividad.class);
    private Actividad currentActividad;
    private final Grid<Actividad> grid = new Grid<>(Actividad.class, false);

    @Autowired
    public ActividadesView(ServiciosAdmin service) {
        this.service = service;
        this.currentActividad = new Actividad();

        setSizeFull();

        // PANEL IZQUIERDO: formulario ocupa 30%
        VerticalLayout formWrapper = new VerticalLayout();
        formWrapper.setWidth("30%");
        formWrapper.setHeightFull();
        formWrapper.add(new H3("Formulario Actividad"));

        // Campos del formulario
        TextField tituloField = new TextField("Título");
        TextArea descripcionField = new TextArea("Descripción");
        NumberField precioField = new NumberField("Precio");
        TextField plazasField = new TextField("Plazas");
        DatePicker fechaInicioField = new DatePicker("Inicio Inscripción");
        DatePicker fechaFinField = new DatePicker("Fin Inscripción");
        DatePicker fechaCelebracionField = new DatePicker("Fecha Celebración");
        Button saveButton = new Button("Guardar");

        FormLayout form = new FormLayout();
        form.add(
                tituloField,
                descripcionField,
                precioField,
                plazasField,
                fechaInicioField,
                fechaFinField,
                fechaCelebracionField,
                saveButton
        );

        // Binder bindings
        binder.forField(tituloField)
                .asRequired("Título obligatorio")
                .bind(Actividad::getTitulo, Actividad::setTitulo);
        binder.forField(descripcionField)
                .bind(Actividad::getDescripcion, Actividad::setDescripcion);
        binder.forField(precioField)
                .asRequired("Precio obligatorio")
                .withConverter(
                        Double::floatValue,
                        precioVal -> precioVal == null ? null : Double.valueOf(precioVal),
                        "Precio debe ser un número"
                )
                .bind(Actividad::getPrecio, Actividad::setPrecio);
        binder.forField(plazasField)
                .asRequired("Plazas obligatorias")
                .withConverter(
                        Integer::valueOf,
                        String::valueOf,
                        "Debe ser un número entero"
                )
                .bind(Actividad::getPlazas, Actividad::setPlazas);
        binder.forField(fechaInicioField)
                .asRequired("Fecha inicio es obligatoria")
                .bind(Actividad::getFechaInicioInscripcion, Actividad::setFechaInicioInscripcion);
        binder.forField(fechaFinField)
                .asRequired("Fecha fin es obligatoria")
                .bind(Actividad::getFechaFinInscripcion, Actividad::setFechaFinInscripcion);
        binder.forField(fechaCelebracionField)
                .asRequired("Fecha celebración obligatoria")
                .bind(Actividad::getFechaCelebracion, Actividad::setFechaCelebracion);

        saveButton.addClickListener(e -> {
            BinderValidationStatus<Actividad> status = binder.validate();
            if (status.hasErrors()) {
                status.getValidationErrors().forEach(err -> Notification.show(err.getErrorMessage()));
                return;
            }
            try {
                binder.writeBean(currentActividad);
                if (service.listarActividadesDisponibles().stream()
                        .noneMatch(a -> a.getId() == currentActividad.getId())) {
                    service.crearActividad(currentActividad);
                    Notification.show("Actividad añadida");
                } else {
                    service.actualizarActividad(currentActividad);
                    Notification.show("Actividad actualizada");
                }
                currentActividad = new Actividad();
                binder.readBean(currentActividad);
                updateGrid();
            } catch (ValidationException | FechaIncorrecta ex) {
                Notification.show("Error: " + ex.getMessage());
            }
        });

        binder.readBean(currentActividad);
        formWrapper.add(form);

        // PANEL DERECHO: grid ocupa 70%
        VerticalLayout gridWrapper = new VerticalLayout();
        gridWrapper.setWidth("70%");
        gridWrapper.setHeightFull();
        gridWrapper.add(new H3("Lista de Actividades"));

        // Columnas del grid con tamaños y flex para evitar scroll
        grid.addColumn(Actividad::getId)
                .setHeader("ID")
                .setWidth("60px")
                .setFlexGrow(0);
        grid.addColumn(Actividad::getTitulo)
                .setHeader("Título")
                .setFlexGrow(1);
        grid.addColumn(Actividad::getDescripcion)
                .setHeader("Descripción")
                .setFlexGrow(2);
        grid.addColumn(Actividad::getPrecio)
                .setHeader("Precio")
                .setWidth("80px")
                .setFlexGrow(0);
        grid.addColumn(Actividad::getPlazas)
                .setHeader("Plazas")
                .setWidth("80px")
                .setFlexGrow(0);
        grid.addColumn(Actividad::getFechaInicioInscripcion)
                .setHeader("Inicio Inscripción")
                .setWidth("120px")
                .setFlexGrow(0);
        grid.addColumn(Actividad::getFechaFinInscripcion)
                .setHeader("Fin Inscripción")
                .setWidth("120px")
                .setFlexGrow(0);
        grid.addColumn(Actividad::getFechaCelebracion)
                .setHeader("Celebración")
                .setWidth("120px")
                .setFlexGrow(0);

        grid.addComponentColumn(act -> { // Acciones(act -> {
            Button edit = new Button("Editar");
            Button delete = new Button("Borrar");
            edit.addClickListener(ev -> {
                currentActividad = act;
                binder.readBean(currentActividad);
            });
            delete.addThemeVariants(ButtonVariant.LUMO_ERROR);
            delete.addClickListener(ev -> {
                service.borrarActividad(act.getId());
                Notification.show("Actividad eliminada");
                updateGrid();
            });
            return new HorizontalLayout(edit, delete);
        }).setHeader("Acciones").setAutoWidth(true);

        grid.setSizeFull();
        gridWrapper.add(grid);

        add(formWrapper, gridWrapper);
        updateGrid();
    }

    private void updateGrid() {
        grid.setItems(service.listarActividadesDisponibles());
    }
}
