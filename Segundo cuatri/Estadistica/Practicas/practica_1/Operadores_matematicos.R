mi_vector<-c(1,2,3,4,6)
print(mi_vector)

mi_factor<-factor(c("bajo","medio","alto","medio"))
print(mi_factor)

mi_lista<-list(numeros=1:5,palabras=c("Hola","mundo"))
print(mi_lista)
mi_lista$numeros

mi_dataFrame<-data.frame(
  nombres=c("Ana","Juan","Maria"),
  edades=c(23,35,28),
  alturas=c(1.65,1.8,1.7)
)
print(mi_dataFrame)

a<-10
b<-3
modulo<-a%%b
division_entera<-a%/%b
