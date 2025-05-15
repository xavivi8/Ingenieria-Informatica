# 03.21 Generación de sitios web estáticos con Vuepress

##  Autores

* Carlos Martínez Sánchez  (@cms00065)
* Gonzalo Carcelén Gómez   (@gcg00035)

## Descripción breve

El proyecto expone la forma de generar un sitio web estático mediante VuePress, una herramienta sencilla e intuitiva que con 
una ligera configuración se logra una apariencia atractiva.

## Bibliografía y referencias

A continuación, se listan las referencias más relevantes mencionadas en la presentación (diapositiva 31) para profundizar en el tema:
* Primeros Pasos para la configuración: [Tutotial Web] (https://kinsta.com/es/blog/vuepress/#:~:text=VuePress%20en%20Kinsta-,%C2%BFQu%C3%A9%20es%20VuePress%3F,uso%20por%20la%20que%20Vue)
* Página Oficial de VuePress: [Documentación Vuepress] (https://vuepress.vuejs.org/guide/introduction.html)
* Página Oficial de la documentación del tema por defecto: [Documentación Default Theme] (https://ecosystem.vuejs.press/themes/default/config.html)


## Inteligencias Artificales Generativas empleadas
* **[ChatGPT](https://chatgpt.com/)**: Ayudó a estructurar la presentación y generación de recetas
* **[Gemini](https://gemini.google.com/app)**: Útil para buscar información histórica sobre el VuePress y el FrameWork

## Materiales complementarios
* Carpeta **Docs**: En ella nos encontramos las siguientes subcarpetas
  * .vuepress → Contiene todos los archivos relativos a la configuración del sitio
    * styles → Contiene la hoja de estilos `index.scss` que contiene las clases de estilos que se aplican a los html
    * dist → Carpeta generada por VuePress al hacer build del proyecto
    * ``config.js`` → Archivo de configuración donde se importa el tema utilizado, configuraciones iniciales (título, idioma, URL base...) y se declaran elementos relativos a la web (Menu, Barra Lateral de Navegación...)
  * recetas → Contiene todos las páginas redactadas en ficheros .md
  * `README.md` → Página principal del sitio web estático

> Para desplegar este proyecto se deberán seguir las instrucciones que aparecen en la presentación (Diapositiva 12)