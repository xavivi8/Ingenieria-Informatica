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
  alfa <- 1 - conf.level #nivel de significación
  
  # Estadístico de prueba chi-cuadrado
  estadistico <- gl * varianza / null.value
  
  # Cálculo del p-valor
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