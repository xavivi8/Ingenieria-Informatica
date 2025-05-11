getwd()

setwd("C:/Users/jmart/Documents/GitHub/Ingenieria-Informatica/Primer-Año/Segundo cuatri/Estadistica/Practicas/practica_5")
print("EJERCICIO 1 PUNTO 1")
#--LEER FICHERO--

Tiempos <- scan("Tiempos.txt",
               what   = numeric(),
               dec    = ",",
               quiet  = TRUE)
#-----------------------------------------------------------------------------
  #--INTERVALO DE CONFIANZA 90%--[[busca ( -Inf )
  
print(t.test(Tiempos, conf.level = 0.9))
-----------------------------------------------------------------------------
----------------print("EJERCICIO 1 PUNTO 2")---------------------------------
  #]]--MAXIMA MEDIA DEL INTERVALO--[[
  
print(t.test(Tiempos, alternative = "less", conf.level = 0.9))
-----------------------------------------------------------------------------
----------------print("EJERCICIO 1 PUNTO 3")---------------------------------
  #]]--Contrastamos que la media es 3 contra que es mayor que 3--[[
  
print(t.test(Tiempos, alternative = "greater", mu = 3, conf.level = 0.9))##0,9= 1-0,1 del enunciado
----------------print("EJERCICIO 1 PUNTO 4")---------------------------------
  #]]--Intervalo conf. de 90% a la dispersion,--[[copiamos varianza.text y miramos el intervalo
                                               
varianza.test <- function(x, null.value = 1, alternative = c("two.sided", "less", "greater"),
                          conf.level = 0.95) {
  NombreVariable <- deparse(substitute(x))
  n <- length(x)
  if (n < 2) {
    stop("Se necesitan al menos 2 datos para realizar la prueba.")
  }
  if (is.null(alternative)){
    alternative=c("two.sided")
  }
  varianza <- var(x)  #Cuasivarianza
  gl <- n - 1   #Grados de libertad
  alfa <- 1 - conf.level #nivel de significaci?n
  
  # Estadistico de prueba chi-cuadrado
  estadistico <- gl * varianza / null.value
  
  # Calculo del p-valor
  if (alternative[1] == "two.sided") {
    p.value <- 2 * min(pchisq(estadistico, df = gl), 1 - pchisq(estadistico, df = gl))
    # Intervalo de confianza
    chi2_Inf <- qchisq(1 - alfa / 2, df = gl)
    chi2_Sup <- qchisq(alfa / 2, df = gl)
    conf.int <- c(gl * varianza / chi2_Inf, gl * varianza / chi2_Sup)
    
  } else if (alternative[1] == "less") {
    p.value <- pchisq(estadistico, df = gl)
    # Intervalo de confianza
    chi2_Sup <- qchisq(alfa, df = gl)
    conf.int <- c(0, gl * varianza / chi2_Sup)
  } else if (alternative[1] == "greater") {
    p.value <- 1 - pchisq(estadistico, df = gl)
    # Intervalo de confianza
    chi2_Inf <- qchisq(1 - alfa , df = gl)
    conf.int <- c(gl * varianza / chi2_Inf, Inf)
  } else {
    stop("La alternativa debe ser 'two.sided', 'less' o 'greater'.")
  }
  
  attr(conf.int,"conf.level") <- conf.level
  
  # Resultado
  result <- list(
    statistic = c("Chi-squared" = estadistico),
    parameter = c(df = gl),
    p.value = p.value,
    conf.level=conf.level,
    conf.int = conf.int,
    estimate = c("sample variance" = varianza),
    null.value = c("variance" = null.value),
    alternative = alternative[1],
    method = "Chi-squared test for variance",
    data.name = NombreVariable
  )
  class(result) <- "htest"
  return(result)
}
print(varianza.test(Tiempos, conf.level = 0.9))## esta es la linea clave
-----------------------------------------------------------------------------
----------------print("EJERCICIO 1 PUNTO 5")---------------------------------
  #]]--La dispersion difiere de 0,5 segundos--[[dan dispersion y saco varianza, p-valor debe ser mayor a 0,1

#Se compara con 0.25, que es el cuadrado de 0.5, dado que nos dan dispersion para comparar y el codigo trabaja
#con varianza
print(varianza.test(Tiempos, null.value = 0.25, conf.level = 0.9))
----------------print("EJERCICIO 1 PUNTO 6")---------------------------------
  #]]--Si tarda mas de 3,5 s falla, saca intervalo de conf. de 90% usando los fallidos--[[

nfallos <- length(Tiempos[Tiempos > 3.5])##Basta con seleccionar la muestra de fallos con esta linea
nconexiones <- length(Tiempos)
print(prop.test(nfallos, nconexiones, conf.level = 0.9))
#-----------------------------------------------------------------------------