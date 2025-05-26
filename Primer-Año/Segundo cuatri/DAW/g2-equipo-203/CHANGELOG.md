# Changelog

Más información sobre cómo rellenar el fichero en https://keepachangelog.com/es-ES/1.0.0/

## Iteración inicial - 2024-01-30

### Added

- Página de inicio ``index.html`` (María López)
- Imágenes y hojas de estilo (Manuel García)

### Changed

- Añadidos estilos a página de inicio (Manuel García)

## Iteración 0 - 2025-02-21

### Added

- Francisco Javier Martín-Lunas Escobar
  - Vista del login
  - Vista del Navbar
  - Vista artículos
- José Pedrajas De La Torre
  - Vista de empleados
  - Vista facturas
  - Vista de nóminas
- Pedro Jesús Cros Pérez
  - Entidad relación

### Changed

- Francisco Javier Martín-Lunas Escobar
  - README
  - CHANGELOG

## Iteración 1 - 2025-03-07

### Created

- Francisco Javier Martín-Lunas Escobar
  - ArticuloBean
  - Model -> Articulo
  - Plantilla crudPlantilla
- José Pedrajas De La Torre
  - NominaBean
  - EmpleadoBean
  - FacuraBean
  - Model -> Nomina, Empleado, Factura
- Pedro Jesús Cros Pérez
  - Enums => Estado, PayslipStatus, ReceiptStatus, UserRole

### Changed

- Francisco Javier Martín-Lunas Escobar
  - Layout
  - articulos html -> xhtml
  - Pom
- José Pedrajas De La Torre
  - Nomina html -> xhtml
  - Empleado html -> xhtml
  - Factura html -> xhtml

### Moved

- Francisco Javier Martín-Lunas Escobar
  - css de articulos a resources
  - js de articulos a resources
- José Pedrajas De La Torre
  - css de nomina, empleado, factura a resources
  - js de nomina, empleado, factura a resources

  
## Iteración 2 - 2025-03-21

### Created
- Pedro Jesús Cros Pérez
  - Model ↓ // Dejar entidades preparadas para su creación mediante formularios
    - Receipt(factura),Client(cliente), Contact(contacto),
    - Payslip(nómina), ReceiptDetails(detalles de la factura), User(usuario)
  - Model/Dao → GenericDAO, ReceiptDAO, ReceiptDAOJpa, ReceiptDAOMap
  - Controller → ReceiptController
  - WebApp/receipt ↓ // Vista de facturas sin relaciones a otra entidades, pero lo dejo preparado con inputText, redirección a vista una vez se haya completado el formulario, para que en visualiza se confirme si se desea guardar la entidad después de su creación en el formulario
    - createForm.xhtml (alta facturas),
    - home.xhtml (panel de control + listado),
    - read.xhtml (visualiza → read?id="X") 
  - Qualifiers → DAOJpa y DAOMap
  - Componente personalizado → resources/crmcomp/client.xhtml
  - Google Cloud → no consigo mantener en el tiempo la aplicación sin que se cierre en mi máquina virtual de Google
  - >$ mvn clean package
  - >$ mvn payara-micro:bundle
  - >$ java -jar target/crm-microbundle.jar &

- Francisco Javier Martin-Lunas Escobar
  - MenuTemplate.xhtml
  - HeaderFooterTemplate.xhtml
  - loginStep1.xhtml
  - loginStep2.xhtml
  - LoginBean
-José Pedrajas de la Torre
  - Model/Dao → ClientDAO, ClientDAOJpa, ClientDAOMap
  - Controller → ClientController
  - Bean → ClientBean
  -  - WebApp/client ↓ 
  - createForm.xhtml 
  - home.xhtml 
  - read.xhtml 
  - - WebApp/resources/css ↓
  - clients.css
### Changed

- Pedro Jesús Cros Pérez
  - WebApp → menuTemplate.xhtml, crudPlantilla
  - Algunos nombres de directorios comienza por mayúscula → primera minúscula
  - Model ↓ 
    - nombres de variables de **snake case** a **cammel case**
    - comentar relaciones a otras entidades
    - Eliminados atributos no necesarios
- Francisco Javier Martin-Lunas Escobar
  - crudPlantilla.xhtml
  - UserBean
  - README

### Deleted
- Francisco Javier Martin-Lunas Escobar
  - login.xhtml
  - login.css
  - login.js
  - pages/(todos los archivos)

## Iteración 3

### Changed
- Francisco Javier Martin-Lunas Escobar
  - pom.xml
  - persistence.xml
  - web.xml
  - UserBean
  - users\home.xhtml
  - ClientDAOJpa
  - AppConfig
  - User
  - Product
  - ClientDAOJpa
  - persistence.xml
  - MenuTemplate.xhtml
  - web.xml
  - articulo.xhtml -> home.xhtml
  - loginStep1.xhtml
  - loginStep2.xhtml
  - commun.css

- Pedro Jesús Cros Pérez
  - controller/ReceiptController
  - models/Receipt.java añado anotaciones de validaciones
  - models/dao/ReceiptDAOJpa.java
  - resources/META-INF/persistence.xml
  - webapp/receipt/home.xhtml
  - webapp/receipt/add.xhtml
  - webapp/WEB-INF/web.xml
  - webapp/client/*
    - RESUMEN: cambios para corregir entidad Receipt (Factura) para conseguir intercambiar DAOMap -> DAOJpa, para ello hemos tenido que configurar persistence.xml y web.xml para conseguir que payara genere un data-source en un pool-conexiones de esa forma conseguimos la persistencia. Para validaciones con utilizar anotaciones dentro de la clase deseada, además establecer @Valid para verificar que se apliquen esas validaciones. (Estoy investigando porqué cuando levanto la aplicación en http://34.133.224.82/receipt/add.xhtml se produce una excepción, ya que, en local no tengo problemas...)

### Created
- Francisco Javier Martin-Lunas Escobar
  - IUserDAO 
  - UserDaoImpl
  - UserController
  - AppIdentityStore
  - LoginController
  - UserController
  - ProductController
  - AppPrincipal
  - IUserDAO
  - IProductDAO
  - ClienDAOMap
  - UserDAOMap
  - ProductDAOMap
  - UserDAOJpa
  - ProductDAOJpa
  - PasswordHashService
  - messages.properties
  - messages_en.properties
  - /articulos/add
  - /articulos/edit
  - /users/add
  - /users/edit
  - /users/home
  - /users/profile
  - /resources/img/imgDefault.png
  - /resources/img/imgDefault.svg
  - /resources/img/no-image.png
  - /resources/img/poro.jpg

- Pedro Jesús Cros Pérez
  - webapp/receipt/edit.xhtml
  - webapp/receipt/read.xhtml
  - resources/sql/sampledata.sql

### Deleted
- Francisco Javier Martin-Lunas Escobar
  - AppConfig (duplicado)
  - LoginBean
  - ProductBean
  - UserBean
- Pedro Jesús Cros Pérez
  - webapp/receipt/(archivos sin utilizar)
  - models/dao/ (archivos sin utilizar)

### Changed
- José Pedrajas de la Torre
  - ClientController
  - Client
  - Payslip
  - ClientDAOJpa
  - AppConfig
  - ClientDAOMap
  - client/crateForm.xhtml
  - client/home.xhtml

### Created
- José Pedrajas de la Torre
  - IClientDAO
  - ClientDaoImpl
  - PayslipController
  - PayslypDAOJpa
  - PayslipDAOMap
  - IPayslipDAO
  - client/edit
  - payslip/add
  - payslyp/home
  - payslyp/edit

### Deleted
- José Pedrajas de la Torre
  -PayslipBean
- -ClientBean
- client/read

### Iteración 4
Credenciales para iniciar sesión en la aplicación:
 - email: pedro@red.ujaen.es
 - password: pedro

- José Pedrajas de la Torre
  - He añadido el atributo userID a payslip para que cada nómina vaya asociada a su usuario.
  - He creado los componentes de payslip y usuarios para que Javi puede establecer la relacion entre ambas entidades.
  - He usado los componentes de receipt y clientes creado por Pedro para establecer la relacion entre dichas entidades y
    la he representado en la vista historial Facturas.
  - He añadido una imagen para el logo y también la he utilizado de favicon.

- Pedro Jesús Cros Pérez. Mi URL google.cloud: http://34.133.224.82:80
- Gestión CRUD sobre relaciones entre Receipt, ReceiptDetails, Product y User. Añadiendo entidades varias entidades sobre un mismo vistas
    (listado y formularios de creación y edición)
- <b>Creación y utilización de componentes</b> de las entidades (Product, Receipt, ReceiptDetails y User) tanto las foráneas
  - para utilizar dentro de otras entidades (por ejemplo, dentro de factura tiene sus productos, sus detalles y usuarios)
  - todos estos FK. Tanto las originales utilizadas en: Visualiza - _Entidad_?id=X

### Created
- Francisco Javier Martin-Lunas Escobar
  - Creado componente de producto para crear factura mostrará los datos en añadir factura y modificará su cantidad y precio

### Changed
- Francisco Javier Martin-Lunas Escobar
  - Todos los home tienen ahora paginador 

### Iteración 5
- Pedro Jesús Cros Pérez. Mi URL google.cloud: http://34.133.224.82:80
 - Controladores web: Receipt (teniendo en cuenta sus relaciones con ReceiptDetails y Product), Client y User para
utilizar en VUE.
 - DTO's para obtener únicamente las claves foráneas de mis relaciones intersadas, (es decir, los ID de los productos, 
por ejemplo)
 - Vue: 
   - Creación de entidad Receipt eligiendo entidades relacionadas Client y User 
   - Servicios: receipt, user y client
   - Componentes: formulario de creación y edición, listado de Receipt y ErrorList
 - Jose Pedrajas de la Torre. Mi URL google.cloud: http://34.16.53.60/
   - Creacion de metodos para el dao de nóminas con Criteria API getAllPayslip() and deletePayslipByStatus()
   - Creacion de controlador rest Api para la entidad nominas
- Vue:
   - Creacion de entidad Payslip.
   - Servicio para nóminas.
   - Formulario de cración,edición y listado de nóminas
### Change
- Francisco Javier Martin-Lunas Escobar
  - Cmabios en el login para que sea funcional
  - Cambio el eliminar usuario en el dao para que use criteria api y elimine también las nominas relacionados con el usuario

### Created

- Francisco Javier Martin-Lunas Escobar
  - Vista de listado de productos
  - Vista de añadir productos
  - Vista de editar productos
  - servicio de vue para productos
  - Controlador de servidor del back (enviroment)
  - Eliminar productos
  - Crear rouetes para vue
  - Rest api para productos
  - AppCORSAPIFILTER
  - JAXRSConfig
  - CrmValidationException
  - ResponseMessage