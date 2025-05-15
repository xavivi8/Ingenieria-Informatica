# 02.06 Desarrollo de aplicaciones web reactivas con Eclipse Vert.x

##  Autores

* Carlos Jiménez Pelayo (@Cescarplay)
* Carlos Salazar Morales (@Csm00051)
* Pedro Álvarez Gómez (@pag00025)

## Descripción breve

Vert.x es una herramienta reactiva de alto rendimiento que permite construir aplicaciones web 
escalables y asíncronas. En nuestro proyecto de prácticas, la hemos aplicado 
para mostrar las películas recomendadas a partir de una película seleccionada, 
demostrando cómo se pueden gestionar flujos de datos y eventos en tiempo real.

## Bibliografía y referencias

- https://ed.team/blog/que-es-la-programacion-reactiva-y-como-funciona. Una página excepcional que ha servido de gran ayuda
para entender las bases de la programacion reactiva y como funciona.
- https://vertx.io/docs/intro-to-reactive/. Manual de vert.x que explica con detalle el funcionamiento del framework.

## Inteligencias Artificales Generativas empleadas

- Copilot / ChatGPT. Usada para suministrar ejemplos de aplicaciones reactivas usando Vert.x para entender el funcionamiento del framework.

## Materiales complementarios

### Ejemplo 1. 
Dentro encontramos un proyecto basico usando Vert.x. Tenemos una clase **MainVerticle** con su 
test **MainVerticleTest** y varios archivos de configuracion. La aplicacion de Maven ya esta construida, por lo que 
lo unico que hay que hacer para lanzarla, es ejecutar desde la terminal la orden: **mvn exec:java**. Una vez lanzada,
podemos lanzar peticiones con la orden **http** al puerto 8888, o acceder directamente desde el navegador.
- Modo 1. Desde terminal --> ```http http://localhost:8888```
- Modo 2. Desde navegador acceder a --> http://localhost:8888

### Ejemplo 2.
Al ser un ejemplo de como funciona Vert.x implementado en nuestro proyecto de prácticas, los archivos están subidos como
.txt, puesto que sin ejecutarlo con todo el código del proyecto con payara no funcionaría. Lo principal que hemos añadido 
es un documento pdf hecho aparte con una explicación de como se implementa y como funciona sobre nuestro proyecto, puediendo
ser implementado igual para cualquiera y cualquier funcionalidad. El Launcher y el MainVerticle son clases .java que están
en un directorio aparte. El pom lo hemos subido entero pero solo haría falta las dependencias y el plugin mencionadas en el pdf.
recomendaciones es un archivo .js que contiene el script para mostrar las películas relacionadas. paginaPelicula es nuestra vista,
en formato .xhtml y sería donde se vería reflejado el script.

Cabe destacar que las películas relacionadas que hemos puesto, lo hemos hecho de forma fija, es decir, se muestran las mismas
para cualquier película. Esto es debido a que a la hora de implementarlo era más fácil y la intención que teníamos era la de 
enseñar como funciona Vert.x, pero se podría cambiar el script para seleccionar las relacionadas de otra forma.

### Link para la presentacion en CANVA

https://www.canva.com/design/DAGnEfoGGJY/VHCTb0SvHS9haUgpAUe_Vg/edit?utm_content=DAGnEfoGGJY&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton