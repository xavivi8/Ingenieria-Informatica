# 2.05 Autenticación de usuarios y control de acceso con Spring Security

##  Autores

* Alberto Martínez Lombardo  (@aml00138)
* José Alejandro Torres Sáez (@jats0003)

## Descripción breve

Este trabajo tiene como objetivo explorar los fundamentos de la autenticación y el control
de acceso en aplicaciones web basadas en Java, utilizando el framework Spring Security, de 
forma introductoria. A lo largo del trabajo, se ha desarrollado una pequeña aplicación 
(proyecto de prácticas en versión reducida adaptada a Spring) en la que se implementan funcionalidades básicas 
de seguridad, como el registro y login de usuarios, la asignación de roles y la protección de 
rutas según permisos.

## Bibliografía y referencias

### Página oficial de Spring
https://docs.spring.io/spring-security/reference/

### Baeldung
https://www.baeldung.com/security-spring

### Java Guides
https://www.javaguides.net/p/spring-security-tutorial.html

## Inteligencias Artificales Generativas empleadas

### ChatGPT
El principal uso que se le ha dado ha sido para resolver dudas sobre la configuración de 
Spring Security en nuestro proyecto y la validación de contraseñas encriptadas y sin 
encriptar.

## Materiales complementarios

El material complementario suministrado es una versión reducida de nuestro
proyecto de prácticas adaptado a Spring. Es una aplicación donde puedes registrarte 
como usuario e iniciar sesión. Si has iniciado sesión, podrás ver los diferentes eventos
que hay disponibles. En caso de registrarte como administrador, podrás crear
eventos. Se ha proporcionado la clase donde se configura todo lo relacionado con la
seguridad de Spring Security (**SecurityConfig.java**) y la vista jsp donde se muestra
el formulario de login personalizado (**login.jsp**).