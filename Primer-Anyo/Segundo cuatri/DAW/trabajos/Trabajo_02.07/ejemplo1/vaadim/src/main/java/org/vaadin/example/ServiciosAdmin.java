package org.vaadin.example;



import jakarta.annotation.PostConstruct;
import jakarta.validation.Valid;
import org.springframework.stereotype.Service;
import org.springframework.validation.annotation.Validated;
import org.vaadin.example.entidades.Actividad;
import org.vaadin.example.entidades.Socio;
import org.vaadin.example.excepciones.ActividadNoExistente;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

@Service
@Validated
public class ServiciosAdmin {


    private HashMap<Integer,Socio> socios;
    private HashMap<Integer, Actividad> actividades;

    private static final Socio admin = new Socio("admin@admin.com","admin","admin","639658419","$2a$12$QLJH37bBpKLNHVa0daWCqOI.gOtdkuGN4Cwr/vJQZTavUPPdJT55y");

    public ServiciosAdmin(){
        socios = new HashMap<>();
        actividades = new HashMap<>();
    }

    @PostConstruct
    public void init(){
        var a1 = new Actividad("Clases de Cocina Vegetariana", "Explora la cocina vegetariana", 90.0f, 18, LocalDate.now().plusDays(15), LocalDate.now().minusDays(5), LocalDate.now().plusDays(5), "cocinaVegetariana.jpg");
        var a2 = new Actividad("Clases de pilates al aire libre", "Pilates en la playa", 40.0f, 1, LocalDate.now().plusDays(20), LocalDate.now().minusDays(8), LocalDate.now().plusDays(10), "pilates.jpg");
        var a3 = new Actividad("Cata de Vinos y Quesos de Autor", "Experiencia guiada por un sommelier para degustar vinos exclusivos", 120.0f, 15, LocalDate.now().plusDays(12), LocalDate.now().minusDays(12), LocalDate.now().plusDays(3), "cataVinosQuesos.jpg");
        var a4 = new Actividad("Taller de Mixología Premium", "Aprende a preparar cócteles de autor con destilados premium", 80.0f, 12, LocalDate.now().plusDays(25), LocalDate.now().minusDays(15), LocalDate.now().plusDays(8), "mixologia.jpg");
        var a5 = new Actividad("Clase de Yoga en la Azotea", "Sesión de yoga al amanecer con brunch orgánico", 60.0f, 10, LocalDate.now().plusDays(18), LocalDate.now().minusDays(6), LocalDate.now().plusDays(7), "yogaAzotea.jpg");
        var a6 = new Actividad("Torneo de Polo y Brunch Campestre", "Jornada de polo con desayuno gourmet", 150.0f, 20, LocalDate.now().plusDays(30), LocalDate.now().minusDays(20), LocalDate.now().plusDays(12), "poloBrunch.jpg");
        var a7 = new Actividad("Taller de Relojería Suiza y Alta Joyería", "Descubre el arte de la relojería y joyería fina", 200.0f, 5, LocalDate.now().plusDays(22), LocalDate.now().minusDays(10), LocalDate.now().plusDays(9), "relojeriaJoyería.jpg");
        var a8 = new Actividad("Cena Privada con Chef Michelin", "Menú degustación exclusivo con maridaje", 250.0f, 10, LocalDate.now().plusDays(28), LocalDate.now().minusDays(14), LocalDate.now().plusDays(10), "cenaMichelin.jpg");
        var a9 = new Actividad("Cata de Chocolates y Café", "Degustación de chocolates artesanales combinados con cafés de especialidad", 50.0f, 15, LocalDate.now().plusDays(16), LocalDate.now().minusDays(7), LocalDate.now().plusDays(6), "chocolateCafe.jpg");
        var a10 = new Actividad("Proyección de Cine Clásico", "Película clásica con servicio de cócteles y snacks gourmet", 30.0f, 25, LocalDate.now().plusDays(14), LocalDate.now().minusDays(9), LocalDate.now().plusDays(4), "cineClasico.jpg");

        List<Actividad> a = List.of(a1, a2, a3, a4, a5, a6, a7, a8,a9,a10);

        a.forEach(this::crearActividad);
    }

    /**
     *  REGISTRA A UN NUEVO SOCIO
     */
    public Socio crearSocio(@Valid Socio socio) {
        socios.put(socio.getIdSocio(), socio);
        return socio;
    }


    /**
     * CREA UNA NUEVA ACTIVIDAD
     */
    public void crearActividad(@Valid Actividad actividad) {

            actividades.put(actividad.getId(), actividad);
    }








    /**
     *  DEVUELVE UNA ACTIVIDAD DADO SU ID SI SE ENCUENTRA O NULL
     * @return la actividad con las solicitudes cargadas
     */
    public Actividad buscarActividad(int idActividad){
        Actividad a = actividades.get(idActividad);
        if (a != null) {
            return a;
        } else {
            throw new ActividadNoExistente();
        }
    }


    /**
     * Devuelve el objeto socio para logearse
     * @param email email del socio
     * @param clave clave de acceso del socio
     * @return Optional.empty si el login es correcto o Optional.of(Socio) si existe
     */
    /*
    public Optional<Socio> login(@Email String email, String clave) {
        return repositorioSocio.buscarPorEmail(email).filter(socio -> socio.getClaveAcceso().equals(clave));
    }
    */

    /**
     * LISTA LAS ACTIVIDADES DISPONIBLES DE LA TEMPORADA ACTUAL
     * @return arraylist con las actividades
     */
    public List<Actividad> listarActividadesDisponibles(){
        return actividades.values().stream().toList();
    }


    public List<Socio> getAllSocios(){
        return new ArrayList<>(socios.values());
    }


    public void borrarSocio(int idSocio){
        socios.remove(idSocio);
    }

    public void actualizarSocio(Socio currentSocio) {
        socios.put(currentSocio.getIdSocio(), currentSocio);
    }

    public List<Actividad> getAllActividades() {
        return new ArrayList<>(actividades.values());
    }

    public void actualizarActividad(Actividad currentActividad) {
        actividades.put(currentActividad.getId(), currentActividad);
    }

    public void borrarActividad(int idActividad) {
        actividades.remove(idActividad);
    }
}
