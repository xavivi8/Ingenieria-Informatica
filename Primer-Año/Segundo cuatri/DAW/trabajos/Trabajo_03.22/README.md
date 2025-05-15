# 3.22 Creación de aplicaciones de escritorio con html/css/javascript con el framework Electrón

##  Autores

* Abraham García Hurtado  (@brhamuni)
* Diego Rojas Rojas  (@rrr00053)
* Ivan Morales Sánchez  (@ivaanms10)

## Descripción breve

Desarrollo de una aplicación de escritorio utilizando el framework Electron, dirigida tanto a usuarios como a administradores. Los usuarios podrán acceder fácilmente a la página de la pizzería para consultar el menú, hacer pedidos o buscar información relevante. Los administradores, por su parte, tendrán acceso a una interfaz especial donde podrán consultar los datos de la pizzería, como usuarios registrados, el inventario de pizzas, solicitudes de trabajo y estadísticas generales.

## Bibliografía y referencias

* https://dev.to/buildwebcrumbs/exploring-electron-a-javascript-developers-guide-1fjm (Para ver como crear la aplicación en electron.js)
* https://www.electronjs.org/docs/latest/tutorial/quick-start (Para ver como iniciarnos en electron.js)
* https://www.electronjs.org/apps (Para ver las aplicaciones que se han creado con electron.js)

## Inteligencias Artificales Generativas empleadas

* Para el desarrollo de la aplicación, hemos utilizado las principales herramientas de inteligencia artificial generativa (IAG), como Gemini y ChatGPT, las cuales nos han resultado de gran ayuda. Estas herramientas nos han apoyado en la resolución de dudas técnicas y propuestas de diseño, facilitando así el proceso de desarrollo y mejorando la eficiencia del trabajo.
  * ChatGPT: https://chatgpt.com/
  * Gemini: https://gemini.google.com/?hl=es-ES
    
## Materiales complementarios
Descripción breve de los ejemplos suministrados (organizados en subcarpetas en la carpeta de vuestro trabajo) y, si fuera necesario, instrucciones para lanzarlos
* **Instrucciones para lanzar la aplicación:** 
  * Para lanzar la aplicación basta con ir a la terminal, moverse hasta la carpeta del proyecto y ejecutar el siguiente comando:
            
        npm start
    Esto hará que se despliegue electron.js y con ello la app funcional.
  
* El principal problema que hemos encontrado fue al realizar peticiones fetch para obtener los datos desde la API REST, ya que nos surgieron dificultades a la hora de crear los archivos para guardar una copia para cuando no hubiese conexión a internet que la aplicación siguiese siendo funcional.