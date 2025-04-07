### Ejercicio 1
### En los ordenadores de una universidad hay una tasa de infección por un determinado virus informático de 1 :
### 100000 por curso académico.
### Tasa de infección 1/100000. 364000 equipos. Probabilidad de que haya más de 
### 6 casos.
## A) Calcule la probabilidad de que en 364000 equipos aparezcan másde 6 casos en un curso
# I) Utilizando la distribución binomial
# Parámetros
n = 364000
p = 1 / 100000

# P(X > 6) = 1 - P(X <= 6)
prob_mas_de_6 = 1 - pbinom(6, size = n, prob = p)
prob_mas_de_6
# II) utilizando a la aproximación de la binomiala la distribuición de Poisson
# Recuerdá que si n es grande y p pequeño, Bim(n,p) = Poisson(lambda=n*p)
# Parámetro lambda
lambda = n * p

# Probabilidad de más de 6 usando Poisson
# Aproximación Poisson
prob_poisson = 1 - ppois(6, lambda = lambda)
prob_poisson
## b)obtenga el gráfico de las dos funcions masa de probabilidad  y compárelos
x <- 0:15

# FMP Binomial
p_bin <- dbinom(x, size = n, prob = p)

# FMP Poisson
p_pois <- dpois(x, lambda = lambda)

# Graficamos
plot(x, p_bin, type = "h", lwd = 2, col = "blue", ylim = c(0, max(p_bin, p_pois)),
     main = "Comparación FMP: Binomial vs Poisson", ylab = "Probabilidad", xlab = "Casos")
lines(x, p_pois, type = "h", col = "red", lwd = 2)

legend("topright", legend = c("Binomial", "Poisson"), col = c("blue", "red"), lwd = 2)

################################################################################

### Ejercicio 2: Si el número de accesos por minuto a una página web sigue un 
### modelo de Poisson de parámetro lambda=10. Calcule:
### La tasa es de λ = 10 accesos por minuto.
##A) La probabilidad de que en un minuto se produzcan más de tres accesos
## P(X>3)=1−P(X≤3)
lambda <- 10

# P(X > 3)
1 - ppois(3, lambda = lambda)

##B) La probabilidad de que nadie acceda a la página web en 30 segundos.
## Si λ = 10 por minuto, entonces en 30 segundos (0.5 min) → λ = 5
##Queremos P(X=0):
# Lambda para 30 segundos
lambda_30s <- 10 * 0.5

# P(X = 0)
dpois(0, lambda = lambda_30s)

## C) Si a otra página web acceden, por término medio, 5 internautas por minuto,
## ¿cuál es la probabilidad de que en un minuto dado accedan a la página 12 
## internautas?
## Si otra página tiene λ = 5, calcular P(X = 12)
# P(X = 12) con lambda = 5
dpois(12, lambda = 5)


################################################################################

### Ejercicio 3
## A) Determine la distribución de probabilidad de la variable aleatoria X: nº 
## de aciertos en la lotería primitiva.

# Distribución hipergeométrica para la lotería primitiva
m <- 6    # números premiados
n <- 43   # números no premiados
k <- 6    # seleccionados por el jugador

x <- 0:6
prob <- dhyper(x, m = m, n = n, k = k)

# Mostramos la tabla
data.frame(Aciertos = x, Probabilidad = prob)


## B) Represente gráficamente la correspondiente función masa de probabilidad y su
## función de distribución.

# fmp
plot(x, prob, type = "h", col = "blue", lwd = 2,
     main = "FMP - Lotería Primitiva", xlab = "Aciertos", ylab = "Probabilidad")

# Función de distribución
acumulada <- phyper(x, m = m, n = n, k = k)

plot(x, acumulada, type = "s", col = "darkgreen", lwd = 2,
     main = "Función de Distribución Acumulada", xlab = "Aciertos", ylab = "P(X ≤ x)")


## C) Calcule la probabilidad de no obtener premio
# Esto depende de qué consideremos como “premio”. Por lo general, 3 o más 
# aciertos ya da un premio pequeño.
# P(no obtener premio)=P(X<3)=P(X≤2)

# Probabilidad de no obtener premio (0, 1 o 2 aciertos)
phyper(2, m = m, n = n, k = k)

### Ejercicio 4: Cuando en una distribución binomial np > 10, la aproximación 
### que se lleva a cabo es a la distribución normal. Por ejemplo, calcule la
### probabilidad de obtener entre 45 y 55 caras cuando tiramos una moneda 
### equilibrada 100 veces:
### Se lanza una moneda equilibrada 100 veces. Calcular la probabilidad de 
### obtener entre 45 y 55 caras.
## A) utilizando la distribución binomial
# La variable X∼Bin(n=100,p=0.5)
# P(45≤X≤55)=P(X≤55)−P(X<45)=P(X≤55)−P(X≤44)

n <- 100
p <- 0.5

# Probabilidad exacta con binomial
pbinom(55, size = n, prob = p) - pbinom(44, size = n, prob = p)


## B) utilizando la distribución normal
# Cuando np>10, se puede usar la aproximación N(μ=np,σ=sqrt(np(1−p)))
# En este caso:
# μ=50
# σ=sqrt(25)=5
# ¡Y muy importante! Aplicamos corrección por continuidad:
# P(45≤X≤55)≈P(44.5<Z<55.5)

media <- n * p
desv <- sqrt(n * p * (1 - p))

# Aproximación normal
pnorm(55.5, mean = media, sd = desv) - pnorm(44.5, mean = media, sd = desv)


## C) Represente gráficamente la función masa de probabilidad de este modelo 
## binomial y observe su parecido con la densidad de la correspondiente normal.

# Valores posibles
x <- 30:70

# Binomial
fmp <- dbinom(x, size = n, prob = p)

# Normal
densidad <- dnorm(x, mean = media, sd = desv)

# Gráfico comparativo
plot(x, fmp, type = "h", lwd = 2, col = "blue",
     main = "Binomial vs Normal", xlab = "Número de caras", ylab = "Probabilidad")
lines(x, densidad, col = "red", lwd = 2)

legend("topright", legend = c("Binomial", "Normal"), col = c("blue", "red"), lwd = 2)

### Ejercicio 5: Si el tiempo medio que transcurre entre dos conexiones
### consecutivas e independientes a un servidor es 10 segundos, calcule:
### Tiempo medio entre conexiones=10 segundos -> entonces la tasa λ=1/10=0.1 por
### segundo. Esto nos da una distribución Exponencial con rate=0.1
## A) la probabilidad de que transcurran, a lo sumo, 9 segundos.
# P(X≤9)
# Parámetro
rate <- 1 / 10

# Probabilidad acumulada hasta 9
pexp(9, rate = rate)

## B) la probabilidad de que transcurran más de 12 segundos
# P(X>12)=1−P(X≤12)

# P(X > 12)
1 - pexp(12, rate = rate)

## C) los cuantiles de órdenes 0.95 y 0.99, y comente su significado
# P(X≤x)=0.95
# P(X≤x)=0.99

# Cuantil 0.95
qexp(0.95, rate = rate)

# Cuantil 0.99
qexp(0.99, rate = rate)

# El cuantil 0.95 nos dice que el 95% de los intervalos entre conexiones serán 
# menores o iguales al valor que obtengamos. Lo mismo con 0.99, pero para el 
# 99% de los casos