
# 3.6 Creación de interfaces html interactivas con la biblioteca de componentes HTMX

<img src="https://upload.wikimedia.org/wikipedia/commons/6/61/Htmx_Logo.png?20240817130933" width="300" height="90" />


##  Autores

* Antonio Armenteros iranzo  @armenteros04
* David García Padilla  @garcillaa
* Hechun Ouyang  @hechuno

## Descripción breve

HTMX es una tecnología que potencia HTML para la creación de aplicaciones web libre de dependencias. Proporciona una forma más sencilla de desarrollar sitios web dinámicos y eficientes con el poder del hipertexto, ahorrando bastante código en JavaScript, para llamadas a servicios REST, transiciones CSS, WebSockets entre otras funcionalidades.

## Bibliografía y referencias

[HTMX (2025). HTMX docs.](https://htmx.org/docs/) <br>
[HTMX (2025). HTMX examples.](https://htmx.org/examples/)<br>
[Vicente Sancho (2025). HTMX: La tecnología HTML para crear apps web avanzadas.](https://vicentesg.com)<br>
[@rajasegar (2025). GitHub Awesome-HTMX](https://github.com/rajasegar/awesome-htmx)



## Inteligencias Artificales Generativas empleadas

[ChatGPT (2025). GPT-4 de OpenAI.](https://chatgpt.com/?model=auto ) <br>
* Explicación de ejemplos y código

[Claude (2025). Anthropic 3.7 Sonnet.](https://claude.ai/new)<br>
* Generación de código



## Materiales complementarios

### Ejemplo 1
  
En este ejemplo, HTMX se usa para realizar una petición HTTP DELETE al hacer clic en el botón, y animar su desaparición con una transición de opacidad.

```
hx-delete="/fade_out_demo"
```
Indica que al hacer clic en el botón, se enviará una petición HTTP DELETE a la URL /fade_out_demo.

```
hx-swap="outerHTML swap:1s"
```
Especifica que el contenido del botón será reemplazado (outerHTML) con la respuesta del servidor, y que la transición de este reemplazo debe durar 1 segundo (swap:1s).

```
Clase CSS .fade-me-out.htmx-swapping
```
Htmx agrega la clase htmx-swapping justo antes de que ocurra el reemplazo. En este caso, cuando esto ocurre, el botón se desvanece con una transición CSS de opacidad a 0 durante 1 segundo.


### Ejemplo 2

Este ejemplo muestra cómo se usa HTMX para crear un buscador interactivo de ejercicios sin necesidad de escribir JavaScript adicional el cual hemos usado para nuestro proyecto de prácticas TERCFIT.

```
hx-get="/api/ejercicios"
```
Cada vez que se detecta una interacción (ver siguiente punto), HTMX realiza una petición GET a la ruta /api/ejercicios.
```
hx-trigger="keyup changed delay:200ms, load"
```
Define cuándo debe hacerse la petición:

* keyup: cuando el usuario escribe en el campo.

* changed: cuando el contenido cambia.

* delay:200ms: espera 200ms desde el último evento para evitar hacer demasiadas peticiones.

* load: hace una primera petición automáticamente al cargar la página.
```
hx-target="#resultados"
```
Indica que la respuesta del servidor se insertará en el div id="resultados".

Al escribir en el campo de búsqueda, se envía automáticamente una petición GET al servidor (a /api/ejercicios), y los resultados se muestran en el div sin recargar la página. Esto crea un buscador en tiempo real, dinámico y fluido, solo usando atributos de HTMX, sin escribir JavaScript.

Finalmente en este ejemplo también se encuentra un video para ver el funcionamiento dentro de la WebApp, nuestro código de la API REST implementado y el script de instalación y configuración de HTMX.
