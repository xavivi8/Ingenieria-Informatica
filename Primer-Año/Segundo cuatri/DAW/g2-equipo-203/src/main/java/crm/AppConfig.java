package crm;

import crm.enums.PayslipStatus;
import crm.enums.UserRole;
import crm.models.*;
import crm.persistence.ReceiptDAO;
import crm.persistence.ReceiptDetailsDAO;
import crm.persistence.IClientDAO;
import crm.persistence.IProductDAO;
import crm.persistence.IUserDAO;
import crm.qualifiers.DAOJpa;
import crm.service.PasswordHashService;
import jakarta.enterprise.context.ApplicationScoped;
import jakarta.enterprise.event.Observes;
import jakarta.enterprise.event.Startup;
import jakarta.enterprise.inject.Default;
import jakarta.faces.annotation.FacesConfig;
import jakarta.inject.Inject;
import jakarta.inject.Named;
import jakarta.security.enterprise.authentication.mechanism.http.CustomFormAuthenticationMechanismDefinition;
import jakarta.security.enterprise.authentication.mechanism.http.LoginToContinue;
import org.glassfish.soteria.identitystores.annotation.Credentials;
import org.glassfish.soteria.identitystores.annotation.EmbeddedIdentityStoreDefinition;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Logger;

import static java.util.logging.Logger.getLogger;

@EmbeddedIdentityStoreDefinition({
        @Credentials(callerName = "admin@gmail.com", password = "secret1", groups = {"ADMIN"}),
        @Credentials(callerName = "daw1@red.ujaen.es", password = "123456", groups = {"ADMIN"}),
        @Credentials(callerName = "pedro@red.ujaen.es", password = "pedro", groups = {"ADMIN"})
})
@CustomFormAuthenticationMechanismDefinition(
        loginToContinue = @LoginToContinue(
                loginPage = "/auth/loginStep1.xhtml",
                errorPage = "",
                useForwardToLogin = false
        )
)
@FacesConfig //enable JSF front-controller
@Named("app")
@Default
@ApplicationScoped
public class AppConfig {

    @Inject
    private AppIdentityStore appIdentityStore;

    //@Inject @DAOMap
    @Inject
    @DAOJpa
    IUserDAO userDao;

    @Inject
    @DAOJpa
    ReceiptDAO receiptDAO;
    @Inject
    @DAOJpa
    ReceiptDetailsDAO receiptDetailsDAO;

    @Inject
    @DAOJpa
    IClientDAO clientDAOJPA;

    @Inject
    @DAOJpa
    IProductDAO productDAO;

    @Inject
    private PasswordHashService passwordHashService;

    private final Logger log = getLogger(AppConfig.class.getName());

    public AppConfig() {
        log.info(">>> Application starting...");
    }

    /**
     * Automatically called when all dependencies are satisfied
     */
    public void onStartup(@Observes Startup event) {
        log.info(">>> Application ready");
        createSampleData();
    }

    public void createSampleData() {
        log.info("Creando clientes de prueba");

        String encryptedPassword1 = passwordHashService.encryptPassword("1234");
        String encryptedPassword2 = passwordHashService.encryptPassword("123456");

        User u1 = new User("jmartinlunasescobar@gmail.com", encryptedPassword1, "Javi", "23248484N", UserRole.ADMIN);
        u1.setSurname("Martín");
        u1.setPhone("600123456");

        User u2 = new User("daw2@red.ujaen.es", encryptedPassword2, "Daw", "23123454N", UserRole.ADMIN);
        u2.setSurname("Prueba");
        u2.setPhone("600654321");

        log.info("Creando usuario: " + u1);
        userDao.createUser(u1);
        userDao.createUser(u2);

        userDao.createUser(
                new User("pedroRRHH@red.ujaen.es"
                        , passwordHashService.encryptPassword("pedro")
                        , "Pedro"
                        , "11111111H"
                        , UserRole.RRHH)
        );

        createClients();
        createProducts();
        createReceipts();

        List<Receipt> receiptsReadAll = receiptDAO.readAll();
        List<Receipt> receiptsReadUserOrClient = receiptDAO.searchByUserOrClient(2L,2L);
        List<Receipt> receiptsReadMinPriceOrUser = receiptDAO.searchByMinPriceOrUser(3L, 23.0);
        //Integer dataDeleted = receiptDAO.deleteByTotalPriceGreaterThan(23.0);
        List<Receipt> receiptsReadAll2 = receiptDAO.readAll();

    }

    public void createClients() {
        clientDAOJPA.createClient(
                new Client("Ana Martínez", "ana.martinez@red.ujaen.es", "623456789")
        );
        clientDAOJPA.createClient(
                new Client("Luis Gómez", "luis.gomez@red.ujaen.es", "687654321")
        );
        clientDAOJPA.createClient(
                new Client("María Fernández", "maria.fernandez@red.ujaen.es", "611222333")
        );
        clientDAOJPA.createClient(
                new Client("Carlos Rodríguez", "carlos.rodriguez@red.ujaen.es", "699888777")
        );
        clientDAOJPA.createClient(
                new Client("Elena Sánchez", "elena.sanchez@red.ujaen.es", "619995555")
        );
    }

    public void createReceipts() {
        Receipt r1Created = receiptDAO.create(new Receipt(null, LocalDate.of(2025, 4, 22), 9876, 2L, 2L));
        Receipt r2Created = receiptDAO.create(new Receipt(null, LocalDate.of(2025, 4, 22), 0, 2L, 2L));
        Receipt r3Created = receiptDAO.create(new Receipt(null, LocalDate.of(2025, 4, 23), 0, 3L, 3L));
        Receipt r4Created = receiptDAO.create(new Receipt(null, LocalDate.of(2025, 4, 30),  789.90, 5L, 2L));
        Receipt r5Created = receiptDAO.create(new Receipt(null, LocalDate.of(2025, 4, 15), 4500.00, 1L, 5L));
        Receipt r6Created = receiptDAO.create(new Receipt(null, LocalDate.of(2025, 3, 12),   67.40, 4L, 2L));
        Receipt r7Created = receiptDAO.create(new Receipt(null, LocalDate.of(2025, 2, 28),  125.99, 3L, 6L));
        Receipt r8Created = receiptDAO.create(new Receipt(null, LocalDate.of(2025, 1, 10),20000.00, 1L, 3L));
        Receipt r9Created = receiptDAO.create(new Receipt(null, LocalDate.of(2024, 12, 25),  59.99, 2L, 2L));
        Receipt r10Created = receiptDAO.create(new Receipt(null, LocalDate.of(2024, 11, 2), 876.50, 5L, 4L));
        Receipt r11Created = receiptDAO.create(new Receipt(null, LocalDate.of(2024, 9, 9), 9999.99, 2L, 1L));
        Receipt r12Created = receiptDAO.create(new Receipt(null, LocalDate.of(2025, 5, 5),   350.75, 3L, 1L));
        Receipt r13Created = receiptDAO.create(new Receipt(null, LocalDate.of(2025, 5, 7),  1020.00, 2L, 4L));

        List<ReceiptDetails> rdList = createReceiptDetailsFKReceipts(); // 24 total

        // Añado detalles a facturas
        r1Created.setDetails(List.of(rdList.get(0), rdList.get(1), rdList.get(2), rdList.get(3)));
        Receipt r1Updated = receiptDAO.update(r1Created);
        r2Created.setDetails(List.of(rdList.get(4), rdList.get(5), rdList.get(6), rdList.get(7)));
        Receipt r2Updated = receiptDAO.update(r2Created);
        r3Created.setDetails(List.of(rdList.get(8), rdList.get(9), rdList.get(10), rdList.get(11)));
        Receipt r3Updated = receiptDAO.update(r3Created);
        r4Created.setDetails(List.of(rdList.get(12), rdList.get(13), rdList.get(14), rdList.get(15)));
        Receipt r4Updated = receiptDAO.update(r4Created);
        r5Created.setDetails(List.of(rdList.get(16), rdList.get(17), rdList.get(18), rdList.get(19)));
        Receipt r5Updated = receiptDAO.update(r5Created);
        r6Created.setDetails(List.of(rdList.get(0), rdList.get(4), rdList.get(8)));
        Receipt r6Updated = receiptDAO.update(r6Created);
        r7Created.setDetails(List.of(rdList.get(1), rdList.get(5), rdList.get(9)));
        Receipt r7Updated = receiptDAO.update(r7Created);
        r8Created.setDetails(List.of(rdList.get(2), rdList.get(6), rdList.get(10), rdList.get(14)));
        Receipt r8Updated = receiptDAO.update(r8Created);
        r9Created.setDetails(List.of(rdList.get(3), rdList.get(7), rdList.get(11), rdList.get(15)));
        Receipt r9Updated = receiptDAO.update(r9Created);
        r10Created.setDetails(List.of(rdList.get(12), rdList.get(16), rdList.get(18)));
        Receipt r10Updated = receiptDAO.update(r10Created);
        r11Created.setDetails(List.of(rdList.get(13), rdList.get(17), rdList.get(19)));
        Receipt r11Updated = receiptDAO.update(r11Created);
    }

    public void createProducts() {
        productDAO.createProduct(new Product(
                null,
                "Portátil Gamer X15",
                "Portátil con procesador Intel i9, 32 GB RAM y GPU RTX 3080",
                1999.99,
                15
        ));
        productDAO.createProduct(new Product(
                null,
                "Smartphone Ultra Z",
                "Teléfono con pantalla OLED 6,7\", 128 GB y triple cámara",
                899.50,
                50
        ));
        productDAO.createProduct(new Product(
                null,
                "Auriculares Inalámbricos SoundFree",
                "Auriculares Bluetooth con cancelación de ruido activa",
                129.00,
                200
        ));
        productDAO.createProduct(new Product(
                null,
                "Monitor 4K ProView 27\"",
                "Monitor IPS 4K de 27 pulgadas con 100 % sRGB",
                459.75,
                30
        ));
        productDAO.createProduct(new Product(
                null,
                "Teclado Mecánico RGB",
                "Teclado compacto con switches Cherry MX Red y retroiluminación RGB",
                79.95,
                120
        ));
        productDAO.createProduct(new Product(
                null,
                "Ratón Ergonómico GripMaster",
                "Ratón vertical con sensor óptico de 6400 DPI",
                49.99,
                75
        ));
        productDAO.createProduct(new Product(
                null,
                "SSD NVMe 1 TB TurboFast",
                "Unidad interna NVMe PCIe Gen4 de 1 TB",
                149.90,
                60
        ));
        productDAO.createProduct(new Product(
                null,
                "Cámara Web HD StreamCam",
                "Cámara USB 1080p a 60 fps con micrófono integrado",
                59.95,
                90
        ));
        productDAO.createProduct(new Product(
                null,
                "Barra de Sonido SoundBar 300",
                "Barra de sonido Bluetooth con subwoofer inalámbrico",
                199.00,
                40
        ));
        productDAO.createProduct(new Product(
                null,
                "HDD Externo 2 TB BackupSafe",
                "Disco duro USB 3.0 de 2 TB para copias de seguridad",
                89.50,
                85
        ));
    }

    public List<ReceiptDetails> createReceiptDetailsFKReceipts() {
        List<ReceiptDetails> receiptDetailsFK = new ArrayList<>();

        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 2L, 4))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 3L, 27))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 2L, 3))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 4L, 10))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 1L,  8))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 5L, 12))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 6L, 20))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 7L, 15))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 8L,  2))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 9L, 30))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 1L,  6))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 3L, 25))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 4L, 18))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 5L,  9))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 6L, 11))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 7L,  4))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 8L, 50))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 2L, 13))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 9L,  7))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null,10L, 22))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 3L,  5))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 4L, 28))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 1L, 17))
        );
        receiptDetailsFK.add(
                receiptDetailsDAO.create(new ReceiptDetails(null, 6L,  3))
        );


        return receiptDetailsFK;
    }

    public UserRole[] getAvailableRoles() {
        return UserRole.values(); // Devuelve todos los valores del enum
    }

    public PayslipStatus[] getAvailableStatus() {
        return PayslipStatus.values();
    }
}
