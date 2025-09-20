package org.vaadin.example.views;

import com.vaadin.flow.component.html.H3;
import com.vaadin.flow.component.html.Image;
import com.vaadin.flow.component.html.Paragraph;
import com.vaadin.flow.component.html.Span;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.component.orderedlayout.FlexComponent;
import com.vaadin.flow.router.Route;
import org.springframework.beans.factory.annotation.Autowired;
import org.vaadin.example.ServiciosAdmin;
import org.vaadin.example.entidades.Actividad;
import org.vaadin.example.layouts.MainLayout;

import java.time.format.DateTimeFormatter;
import java.util.List;

@Route(value = "actividades-cards", layout = MainLayout.class)
public class ActividadesCardsView extends VerticalLayout {

    private final DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");

    @Autowired
    public ActividadesCardsView(ServiciosAdmin service) {

        setSizeFull();
        setPadding(true);
        setSpacing(true);

        // Título de la página
        add(new H3("Lista de Actividades"));

        // Contenedor horizontal con scroll
        HorizontalLayout cardsContainer = new HorizontalLayout();
        cardsContainer.setWidthFull();
        cardsContainer.setPadding(false);
        cardsContainer.setSpacing(true);
        cardsContainer.setAlignItems(FlexComponent.Alignment.START);
        cardsContainer.getStyle()
                .set("overflow-x", "auto")
                .set("padding", "1rem")
                .set("box-sizing", "border-box");

        // Crear tarjetas para cada actividad
        List<Actividad> actividades = service.getAllActividades();
        for (Actividad act : actividades) {
            VerticalLayout card = new VerticalLayout();
            card.setWidth("250px");
            card.setPadding(true);
            card.setSpacing(false);
            card.getStyle()
                    .set("background", "#f9f9f9")
                    .set("border-radius", "8px")
                    .set("box-shadow", "0 2px 4px rgba(0,0,0,0.1)")
                    .set("padding", "1rem")
                    .set("box-sizing", "border-box");

            // Imagen: se sirve desde META-INF/resources/frontend
            String filename = act.getImagen(); // e.g. "cataVinosQuesos.jpg"
            Image foto = new Image("/frontend/" + filename, act.getTitulo());
            foto.setWidthFull();
            foto.getStyle().set("border-radius", "4px 4px 0 0");

            // Título
            Span cardTitle = new Span(act.getTitulo());
            cardTitle.getStyle()
                    .set("font-size", "1.1rem")
                    .set("font-weight", "600")
                    .set("margin-top", "0.5rem");

            // Descripción
            Paragraph desc = new Paragraph(act.getDescripcion());
            desc.getStyle().set("margin", "0.5rem 0");

            // Fecha de celebración
            Span fecha = new Span("Fecha: " + act.getFechaCelebracion().format(dateFormatter));
            fecha.getStyle()
                    .set("font-size", "0.9rem")
                    .set("color", "#555");

            card.add(foto, cardTitle, desc, fecha);
            cardsContainer.add(card);
        }

        add(cardsContainer);
    }
}