#Ejercicio 1
#2. Genere un dataFrame a partir de los datos anteriores
ejer2<-data.frame(
  Antiguedad<-c(15,19,14,3,10,18,11,5,20,14),
  Categoria<-c("Mid","Junior","Senior","Senior","Junior","Senior","Mid","Junior","Senior","Junior"),
  Errores_Cometidos<-c(33,28,4,7,11,12,17,32,26,24),
  Salario_Mensual<-c(4794,4503,5925,3182,2751,5280,2373,3841,4081,6611)
)

#3. ¿Cuántas variables e individuos hay en los datos? Almacénelos en variables e imprima 
#los valores con sus respectivos textos

variables<-length(ejer2)
print(paste("Variables",variables,""))

individuos<-length(ejer2$Antiguedad)
print(paste("Individuos",individuos))

#4. Suponiendo que son todos los trabajadores de una empresa. ¿Cuánto paga mensualmente
#la empresa a sus trabajadores?
sum(ejer2$Salario)

#5. Cree una función llamada media que acepte como parámetro un vector y devuelva la 
# media de los valores del vector. Úsala para conocer el salario medio de los 
# trabajadores de la empresa
media <- function(vector){
  return<-mean(vector)
}
print(media(ejer2$Salario))

#6. Genere una muestra de 5 programadores. ¿Cuál es su salario medio? ¿Y el salario 
# máximo? ¿Y el mínimo?
programadores<-sample(ejer2$Salario)
programadores
mean(programadores)
max(programadores)
min(programadores)

#7. Almacene en un vector los números divisibles por 5 desde 5 a 100. ¿Cuántos 
# elementos tiene el vector?
divisibles<-seq(from=5,to=100,by=5)
divisibles

#8. Genere el siguiente vector (-3,-2.9,. . . 0,0.1,0.2,. . . .3) ¿Cúal es su media?
vect8<-seq(from-3,to=3,by=0.1)
vect8
mean(vect8)

#9. Genere el siguiente vector (1, 2, 3, . . . , 19, 20, 19, 18, . . . , 2, 1). 
# Obtener un vector con los valores acumulados hasta ese elemento incluido el mismo.
ejer9<-c(1:20,19:1)
ejer9
suma_acumulada<-cumsum(ejer9)
suma_acumulada

#10. Genere una función llamada momento_k que acepte como parámetros un vector (x) 
# y un entero positivo (k). La función debe devolver
momento_k <-function(x,n) {
  if(x==0||n<=0) {
    stop("x debe ser diferente a 0 y n deve ser entero positivo")
  }
  suma<-sum((x^n)/n)
  return(suma)
}

resultado10<-momento_k(5,8)
prunt(resultado10)

#11. Programe una función llamada coef.asimetria que acepte un vector x y devuelva
# el coeficiente de asimetría de Fisher, esto es
coef.asimetria <- function(x){
  n<-lenght(x)
  media<-mean(x)
  S<-sd(x)
  asim<-(sum(x-media)^3)/n*S^3
  return(asim)
}

resultado_asimetria<-coef.asimetria(c(10,12,15,14,18,20,22))
print(resultado_asimetria)

#12.  Programe una función llamada coef.curtosis que acepte un vector x y 
# devuelva el coeficiente de curtosis de Fisher, esto es
coef.curtosis <- function(x) {
  n<-lenght(x)
  media_x<-mean(x)
  sd_x<-sd(x)
  curtosis<-sum((x-media_x)^4)/(n*sd_x^4) - 3
  return(curtosis)
}

resultado_curtosis<-coef.curtosis(c(10,12,15,14,18,20,22))
print(resultado_curtosis)