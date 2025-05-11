# Changelog

## Trabajo voluntario

### Participantes

- Francisco Javier Martín-Lunas Escobar
- Pedro Jesús Cros Pérez

### Funcionalidades
- Pedro Jesús Cros Pérez
  - Crear Leer Eliminar Actualizar Factura
  - Formulario Crear y Editar Factura
  - Mappers Factura: DTO's entidad entidadJpa

- Francisco Javier Martín-Lunas Escobar
    - Vista usuarios
    - Añdir usuarios
    - Eliminar usuarios
    - Editar usuarios
    - Vista productos
    - Añadir productos
    - Eliminar productos
    - Editar productos

### Changed

- Pedro Jesús Cros Pérez
  - SpringmvcProjectApplication
  - application.properties
  - pom.xml

- Francisco Javier Martín-Lunas Escobar
    - SpringmvcProjectApplication
    - application.properties
    - pom.xml

### Created
- Francisco Javier Martín-Lunas Escobar
    - messages.properties
    - messages_en.properties
    - UserRole (enum)
    - User (model)
    - UserRepository (Repository)
    - IUserDao (persistence)
    - UserDAOImpl (persistence/impl)
    - IUserService (service)
    - UserServiceImpl (service/impl)
    - UserDTO (dto)
    - UserController (controller)
    - MiSpringMvcApplication
    - add.jsp (webapp/WEB-INF/jsp/users/)
    - home.jsp (webapp/WEB-INF/jsp/users/)
    - footer-web.tag (webapp/WEB-INF/tags/templates/)
    - header-web.tag (webapp/WEB-INF/tags/templates/)
    - nav-web.tag (webapp/WEB-INF/tags/templates/)
    - index.jsp (webapp/)
    - ChangeLog.md (root)
    - edit.jsp (webapp/WEB-INF/jsp/users/)
    - home.jsp (webapp/WEB-INF/jsp/products/)
    - add.jsp (webapp/WEB-INF/jsp/products/)
    - edit.jsp (webapp/WEB-INF/jsp/products/)

- Pedro Jesús Cros Pérez
  - content/receipt
    - infrastructure
      - capa externa donde se ubican los controladores implementaciones de repositorio y se exige trabajar con la tecnología JPA para persistencia.
    - domain
      - capa interna donde se declara el núcleo del proyecto (entidades e interfaces repositorio)
    - application
      - capa intermedia (capa de servicios) que se encarga de conectar la infraestructura con el dominio. Aquí se encuentran los mappers, interfaces de casos de uso y sus implementaciones de los casos de uso (CRUD - Create, Retrieve, Update, Delete)
  - webapp/WEB-INF/jsp/receipt
    - create. Creación de entidades Receipt
    - edit. Formulario de edicción de entidades Receipt, puedes elegir la entidad desde el PathVariable o RequestParams
    - home. Dashboard principal donde aparecerá un listado de facturas por defecto, creadas en el main de la aplicación
    - read. Vista a la que podrás acceder utilizando PathVariable o RequestParams para seleccionar una factura

### Added
- Francisco Javier Martín-Lunas Escobar
    - resources (carpeta y archivos reciclados del proyecto original)
