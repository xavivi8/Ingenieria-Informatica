package ujaen.daw.springmvcproject;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import ujaen.daw.springmvcproject.content.receipt.domain.entity.Receipt;
import ujaen.daw.springmvcproject.content.receipt.domain.repository.CreateReceiptRepository;
import ujaen.daw.springmvcproject.enums.UserRole;
import ujaen.daw.springmvcproject.models.Product;
import ujaen.daw.springmvcproject.models.User;
import ujaen.daw.springmvcproject.service.IProductService;
import ujaen.daw.springmvcproject.service.IUserService;

import java.time.LocalDate;
import java.util.logging.Logger;

@SpringBootApplication
public class SpringmvcProjectApplication {

    private static final Logger logger = Logger.getLogger(SpringmvcProjectApplication.class.getName());

    public static void main(String[] args) {
        logger.info(">>>Inicializando aplicación");

        SpringApplication.run(SpringmvcProjectApplication.class, args);
    }

    @Bean
    public CommandLineRunner initApp(IUserService userService, IProductService productService, CreateReceiptRepository createReceiptRepository) {
        return args -> {
            // Crear objetos User por defecto y guardarlos en la base de datos
            User user1 = new User("12345678A", "daw1@red.ujaen.es", "12345", "Juan", "Pérez", "123456789", UserRole.ADMIN);
            User user2 = new User("87654321B", "jmartinlunasescobar@gmail.com", "12345", "María", "Luna", "987654321", UserRole.EMPLOYEE);

            // Guardar los usuarios utilizando el servicio
            userService.save(user1);
            userService.save(user2);

            System.out.println("Usuarios iniciales creados.");

            // Crear productos por defecto
            Product product1 = new Product("Producto 1", "Descripción del producto 1", 100.0, 10);
            Product product2 = new Product("Producto 2", "Descripción del producto 2", 150.0, 5);

            // Guardar los productos utilizando el servicio
            productService.save(product1);
            productService.save(product2);

            System.out.println("Productos iniciales creados.");

            // Crear facturas por defecto
            Receipt r1 = new Receipt(LocalDate.now(), "12345678A", 200.0);
            Receipt r2 = new Receipt(LocalDate.now(), "87654321B", 150.0);

            // Guardar los facturas utilizando el servicio
            createReceiptRepository.saveReceipt(r1);
            createReceiptRepository.saveReceipt(r2);

            System.out.println("Recibos iniciales creados.");

        };
    }
}
