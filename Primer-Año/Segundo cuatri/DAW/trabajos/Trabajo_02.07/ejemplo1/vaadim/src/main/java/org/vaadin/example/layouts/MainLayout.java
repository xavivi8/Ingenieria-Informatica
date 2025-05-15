package org.vaadin.example.layouts;

import com.vaadin.flow.component.applayout.AppLayout;
import com.vaadin.flow.component.html.H1;
import com.vaadin.flow.component.orderedlayout.FlexComponent.Alignment;
import com.vaadin.flow.component.orderedlayout.HorizontalLayout;
import com.vaadin.flow.router.RouterLink;
import org.vaadin.example.views.MainView;
import org.vaadin.example.views.ActividadesView;
import org.vaadin.example.views.ActividadesCardsView;

public class MainLayout extends AppLayout {

    public MainLayout() {
        // Título de la aplicación
        H1 logo = new H1("UJA-Sociación");
        logo.getStyle().set("margin", "0").set("font-size", "1.5rem");

        // Enlaces del header
        RouterLink sociosLink    = new RouterLink("Socios", MainView.class);
        RouterLink gestActLink   = new RouterLink("Gestión Actividades", ActividadesView.class);
        RouterLink cardsActLink  = new RouterLink("Tarjetas Actividades", ActividadesCardsView.class);

        HorizontalLayout header = new HorizontalLayout(logo, sociosLink, gestActLink, cardsActLink);
        header.setDefaultVerticalComponentAlignment(Alignment.CENTER);
        header.setWidthFull();

        // Estilo tipo Material: fondo claro y sombra suave, colores por defecto de tema
        header.addClassName("material-header");
        header.getStyle()
                .set("padding", "0.5rem 1rem")
                .set("box-shadow", "0 1px 3px rgba(0,0,0,0.2)");

        addToNavbar(header);
    }
}
