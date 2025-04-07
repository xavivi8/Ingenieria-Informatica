### Ejercicio 1
### En los ordenadores de una universidad hay una tasa de infección por un determinado virus informático de 1 :
### 100000 por curso académico.
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
##A) La probabilidad de que en un minuto se produzcan más de tres accesos