 
# 01.11 Integración de autenticación OpenID en Jakarta 10

##  Autores

* Miguel Bolívar García (@mbg00066)
* Pablo Cañada Carrasco (@pcc00065)

## Descripción breve

Este proyecto consiste en la integración de autenticación federada mediante OpenID Connect en una aplicación desarrollada con Jakarta EE 10 y JSF. Se han implementado dos ejemplos funcionales basados en proveedores externos: uno utilizando **Keycloak** como broker de identidad con **Google** como proveedor, y otro directamente con **Auth0**.

Ambos ejemplos muestran cómo integrar sistemas de autenticación modernos en un proyecto real de prácticas, incorporando el flujo Authorization Code para recuperar y validar tokens de identidad (ID Token), registrar usuarios automáticamente y gestionar el acceso a vistas protegidas dentro de la aplicación.

Se trata de una implementación minimalista y didáctica, pensada para ser entendida, replicada y adaptada fácilmente por otros estudiantes o desarrolladores.

## Bibliografía y referencias

### Referencias

1. **Kawasaki, T.** (2017).  
   [*Diagrams of All The OpenID Connect Flows*](https://darutk.medium.com/diagrams-of-all-the-openid-connect-flows-6968e3990660). Medium.  
   Explicación visual y esquemática de todos los flujos de conexión de OpenID Connect, ideal para comprender cómo funciona Authorization Code Flow, Implicit Flow, Hybrid Flow, etc.


2. **YouTube – Milan Jovanović** (2024).  
   [*¿Qué es Keycloak y cómo configurarlo para implementarlo en un proyecto?*](https://www.youtube.com/watch?v=fvxQ8bW0vO8)  
   Tutorial introductorio que explica qué es Keycloak, cómo instalarlo y configurarlo para utilizarlo como proveedor de identidad en un proyecto real.


3. **YouTube – Coding Together ES** (2023).  
   [*Breve tutorial de cómo implementar Keycloak en Java*](https://www.youtube.com/watch?v=SKNZjg6enKc)  
   Guía corta y práctica para integrar Keycloak con una aplicación Java paso a paso, sin necesidad de configuraciones avanzadas.


4. **Hantsy** (2023).  
   [*What’s new in Jakarta Security 3*](https://itnext.io/what-is-new-in-jakarta-security-3-98db53317e19). ITNEXT.  
   Artículo que muestra un ejemplo funcional del uso de Jakarta Security 3 y cómo integrarlo con Keycloak como proveedor de OpenID Connect.


5. **YouTube – Mathias Conradt** (2019).  
   [*Ejecución y ejemplo de Auth0 con Spring Security*](https://www.youtube.com/watch?v=I0sEY267UKE)  
   Video que demuestra cómo configurar un proyecto de Spring Boot que utiliza Auth0 para autenticación mediante OIDC.


6. **Hughes, A.** (2023).  
   [*Use Jakarta EE 10 with OpenID Connect Authentication*](https://auth0.com/blog/jakarta-ee-oidc/). Auth0 Blog.  
   Tutorial oficial de Auth0 para integrar autenticación basada en OpenID Connect dentro de una aplicación Jakarta EE usando Auth0.


7. **YouTube – Java Day By Day** (2021).  
   [*Breve tutorial de cómo configurar Auth0 para un proyecto*](https://www.youtube.com/watch?v=F-qqUipQUgU)  
   Explicación simple para crear una aplicación en Auth0, configurar los dominios permitidos y obtener el Client ID y Secret necesarios.


## Inteligencias Artificales Generativas empleadas


- **[ChatGPT](https://chat.openai.com/):** Para la generación de código, resolución de errores y comprensión técnica de los servicios y tecnologías utilizadas.

- **[Gemini (Google AI)](https://gemini.google.com/):** Para la creación de contenido visual y textual en las interfaces de usuario, aportando ideas creativas para la presentación de las vistas.
## Materiales complementarios

- ### Ejemplo 1:
Este ejemplo muestra cómo implementar un sistema de autenticación federada con Google utilizando Keycloak como proveedor de identidad (Identity Broker), dentro de una aplicación Java JSF (Jakarta EE) desplegada en Payara.

Este ejemplo está construido sobre el proyecto de prácticas de la asignatura, por lo que en el repositorio solo se incluirán los archivos estrictamente necesarios para mostrar esta implementación (controladores, vistas JSF específicas, configuración de Keycloak y lógica de token).
El proyecto no compilará ni se podrá ejecutar directamente al faltar el resto de la aplicación completa (entidades, DAOs, configuración de base de datos, etc.)

#### Incluye:

- Configuración de Keycloak como broker OpenID con Google como proveedor externo.
- Uso del flujo Authorization Code para obtener el ID token desde Google.
- Decodificación del token para obtener el email del usuario autenticado.
- Registro automático de usuarios nuevos con contraseña temporal.
- Vistas JSF personalizadas para establecer contraseña y acceder al perfil.

#### Cómo probar

- Es necesario **registrarse en la consola de Google Cloud** y crear un nuevo proyecto con credenciales OAuth 2.0. Se genera un `Client ID` y un `Client Secret`.
- En **Keycloak**, dentro del *realm* de nuestra aplicación, se añade un **proveedor de identidad** de tipo *Google*, pegando el `Client ID`, el `Client Secret` y la URI de redirección generada automáticamente por Keycloak.
- En el **proyecto de prácticas (JSF con Jakarta EE)**, se crea un botón que redirige manualmente al endpoint de autenticación de Keycloak con Google.
- Al autenticarse el usuario con Google, Keycloak redirige a la aplicación al archivo `inicio_openid.xhtml`, y se recupera el parámetro `code` desde `UsuarioController`.
- Se implementa en el `UsuarioController` el método `procesarInicioSesionOpenId()`, que:
    - Intercambia el `code` por un `id_token`.
    - Decodifica el `id_token` para obtener el email.
    - Busca o crea el usuario con ese email en nuestra base de datos.
- Si es un usuario nuevo, se le muestra la vista `establecer_contrasenia.xhtml` para que elija una contraseña definitiva.

> **Nota:** Este ejemplo está integrado directamente en el proyecto de prácticas, pero en el repositorio solo se incluirán los archivos clave necesarios para comprender su implementación (controlador, vista, configuración Keycloak).  
> **No funcionará de forma autónoma** sin el resto del proyecto original.

> También pueden añadirse fácilmente otros proveedores de autenticación externos como **Facebook, GitHub, Microsoft**, simplemente creando nuevas credenciales en sus plataformas e incorporándolas como **nuevos proveedores en Keycloak**.


- ### Ejemplo 2:
Este ejemplo muestra cómo implementar un sistema de autenticación externo mediante Auth0 usando el flujo Authorization Code Flow de OpenID Connect, dentro de una aplicación Jakarta EE con JSF.
Se trata de un proyecto sencillo pero totalmente funcional, pensado como base para comprender y reutilizar fácilmente este tipo de integración en aplicaciones reales.

El usuario puede iniciar sesión con una cuenta externa (Auth0, Google...) y tras autenticarse se le redirige a una vista protegida donde se muestran sus datos personales básicos: nombre, alias, correo electrónico y foto de perfil.

#### Incluye:

- Configuración de Auth0 como proveedor OpenID.
  - Uso del flujo Authorization Code para obtener el ID token.
  - Decodificación del token con la librería java-jwt para mostrar datos del usuario autenticado.
  - Redirección protegida mediante FacesContext.
  - Vista personalizada con Bootstrap para una presentación amigable del perfil.

#### Cómo probar:

1. Ejecutar el proyecto en un servidor local (Payara, configurado igual que en los guiones de prácticas de la asignatura).
   2. Acceder a http://localhost:8080/ejemplo2.
   3. Pulsar el botón "Iniciar sesión".
   4. Autenticarse mediante Auth0 (puede usar una cuenta creada o Google).

Verás una vista protegida con los datos del perfil cargados dinámicamente.

5. Pulsar el botón "Cerrar sesión" para poder entrar a la vista restringida con otro usuario.