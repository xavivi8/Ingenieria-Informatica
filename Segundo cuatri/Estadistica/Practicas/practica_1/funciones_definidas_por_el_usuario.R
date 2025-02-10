hola<-function(num) {
  mensaje<-paste("Hola",num)
  return(mensaje)
}
hola(5)

sumar <-function(a,b) {
  resultado<-a+b
  return(resultado)
}
sumar(10,15)

par_impar<-function(num) {
  if(num%%2==0){
    return("Par")
  } else {
    return("Impar")
  }
}
par_impar(7)

area_rectangulo<-function(largo=5,ancho=3){
  area<-largo*ancho
  return(area)
}
area_rectangulo()
area_rectangulo(3,4)

division<-function(a,b){
  cociente<-a%/%b
  residuo<-a%%b
  return(cociente,residuo)
}