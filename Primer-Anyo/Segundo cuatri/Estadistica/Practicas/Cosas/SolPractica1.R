#Ejercicio 1
#-----------

plantilla <- list(Antiguedad = c(15,19,14,3,10,18,11,5,20,14),
                  Categoria = c("Mid","Junior","Senior","Senior","Junior","Senior","Mid","Junior","Senior","Junior"),
                  Errores_cometidos = c(33,28,4,7,11,12,17,32,26,24),
                  Salario_Mensual = c(4794,4503,5925,3182,2751,5280,2373,3841,4081,6611))

#Ejercicio 2
#-----------

df.plantilla <- as.data.frame(plantilla)

#Ejercicio 3
#-----------

dim(df.plantilla)
names(df.plantilla)
antiguedad <- df.plantilla$Antiguedad
antiguedad
categoria <- df.plantilla$Categoria
categoria
errores <- df.plantilla$Errores_cometidos
errores
salario <- df.plantilla$Salario_Mensual
salario

#Ejercicio 4
#-----------

sum(salario)
sum(df.plantilla$Salario_Mensual)

#Ejercicio 5
#-----------

media <- function(x){
  if(length(x) < 1)
    return(NA)
  else
    return(sum(x) / length(x))
}

#Otra forma
media <- function(x){
  ans <- NA
  if(length(x) > 1)
    ans <- sum(x) / length(x)
  return(ans)
}

media(df.plantilla$Salario_Mensual)
media(salario)

#Ejercicio 6
#-----------

muestra <- sample(df.plantilla$Salario_Mensual, 5)
media(muestra)
min(muestra)
max(muestra)

muestra2 <- df.plantilla[sample(1:10,5),]
muestra2
media(muestra2$Salario_Mensual)
min(muestra2$Salario_Mensual)
max(muestra2$Salario_Mensual)

#Ejercicio 7
#-----------

secuencia <- seq(5,100,by=5)
length(secuencia)

#Ejercicio 8
#-----------

v <- seq(-3,3,by=0.1)
media(v)

#Ejercicio 9
#-----------

c(1:20,19:1)
cumsum(c(1:20,19:1))

#Ejercicio 10
#-----------

momento <- function(x,k){
  if (length(x) < 1){
    ans <- NA
  }
  else
    ans <- sum(x ^ k) / length(x)
  return(ans)
}

#Ejercicio 11
#-----------

coef.asimetria <- function(x){
  if (length(x) < 1){
    ans <- NA
  }
  else {
    s <- sqrt(momento(x,2) - media(x) ^ 2)
    ans <- sum((x - media(x)) ^ 3) / (length(x) * s ^ 3)
  }
  return(ans)
}

#Ejercicio 12
#-----------

coef.curtosis <- function(x){
  if (length(x) < 1){
    ans <- NA
  }
  else {
    s2 <- momento(x,2) - media1(x) ^ 2 
    ans <- sum((x - media(x)) ^ 4) / (length(x) * s2 ^ 2) - 3
  }
  return(ans)
}
