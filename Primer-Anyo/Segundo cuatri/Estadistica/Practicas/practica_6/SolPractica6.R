# EJERCICIO
# ---------
getwd()
# Cargamos los datos

load("C:/Users/jmart/Documents/GitHub/Ingenieria-Informatica/Primer-Año/Segundo cuatri/Estadistica/Practicas/practica_5/Compilacion.Rdata")

# Punto 1. Aplicamos el test de rachas

library(DescTools)
RunsTest(Compilacion$Tamano)

# Como el p-valor = 0.1778 > 0.01, no se rechaza la hipótesis nula al 1%. 
# Por tanto, se asume que la muestra ha sido extraida aleatoriamente.

# Punto 2. Obtenemos el diagrama de dispersión del tamaño en función del tiempo

plot(Compilacion$Tamano, Compilacion$Tiempo)
 
# El gráfico muestra una clara relación lineal positiva entre las dos variables
 
# Punto 3. Calculamos el coeficiente de correlación de Pearson

cor(Compilacion$Tiempo, Compilacion$Tamano)

# El coeficiente de correlación lineal de Pearson es 0.9604087, lo que indica 
# fuerte relación lineal positiva.

# Punto 4. Estimamos el modelo

modelo <- lm(Tiempo ~ Tamano, data = Compilacion)
summary(modelo)

# La ecuación del modelo estimado es: ^Tiempo = -0.43862 + 0.40137 · Tamano

# Por cada KB adicional de un fichero latex, el tiempo de compilación aumenta 
# en 0.40137 sg, de media.

# Punto 5. Hacemos el contraste H0: beta1 = 0 frente a H1: beta1 <> 0.

# Sí, ya que se rechaza la hipótesis nula al 1% en el contraste de significación
# individual de la pendiente del modelo (p-valor < 2e-16 < 0.01).

# Punto 6. Hacemos el contraste H0: beta0 = 0 frente a H1: beta0 <> 0

# Al 1% de significación no se rechaza la hipótesis nula en el contraste de 
# significación individual de la constante (p-valor = 0.015 > 0.01), luego se 
# asume que la ordenada en el origen es nula.

# Punto 7

## Normalidad de los residuos

library(car)
qqPlot(modelo$residuals)

## Gráficamente no hay evidencia de falta de normalidad, ya que todos los puntos
## están dentro de las bandas de confianza del gráfico.

shapiro.test(modelo$residuals)

## Objetivamente, como el p-valor = 0.13 > 0.01, no se rechaza la hipótesis nula
## de normalidad de los términos de error al 1%.

## Homocedasticidad

plot(modelo$residuals, modelo$fitted.values)

## Gráficamente, no se observa ningún patrón de embudo ni altavoz.

library(lmtest)
bptest(modelo)
 
## Objetivamente, como el p-valor = 0.4276 > 0.01, no se rechaza la hipótesis 
## nula de homocedasticidad de los términos de error al 1%.

## Ausencia de autocorrelación

plot(modelo$residuals, type = "l")

## Gráficamente, no se observan rachas ni muchos cambios de signo.

dwtest(modelo, alternative = "two.sided")

## Objetivamente, como el p-valor = 0.5484 > 0.01, no se rechaza la hipótesis 
## nula de ausencia de autocorrelación al 1%.

## En definitiva, el modelo supera la fase de diagnosis y se considera adecuado.

# Punto 8. Calculamos un intervalo de confianza para un valor puntual de Y

nuevos.datos = data.frame(Tamano = 25)

predict(modelo, nuevos.datos, interval = c("prediction"), level = 0.99)

# Con una confianza del 99%, el archivo tardará en ser compilado entre 

# Punto 9

# La predicción sí es fiable porque el coeficiente de determinación del modelo 
# es igual a 0.9224, que está por encima de 0.7.
