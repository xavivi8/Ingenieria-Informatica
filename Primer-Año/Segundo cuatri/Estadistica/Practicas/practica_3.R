#->Tablas de frec:
#Frec Abs:
#ni table => frecabs <- table(datos)
#Ni cumsum(frecabs)
#Frec Rela:
#fi prop.table(frecabs)
#Fi cumsum(frecrel)
#
#-----
#Tabla <- data.frame(
#  Nombre= names(frecabs)
#  ni=as.vector(frecabs)
#  Ni=cumsum(as.vect)
#  fi=
#  Fi=
#)
#->Graficos:
#Graficos:
#-Barras, barplot
#-Sectores, pie
#-C.acumula,plot->frec.acum
#-Histograma,hist
#-P.frecuencia,plot
#->Med. Posicion, dispersion y forma
#Media, mean
#Mediana, median
#Moda, Mode
#Cuantilesquantile
#Var
#Dt,sd
#dv.sd/mean
#CuasiVar:var
#coef curt, Kurt(Datosmeth=A)
#->DV anomalos
#R.I |QR(Datos,type=2)
#D.Caja y bigotes Boxplot=>Salida<-boxplot

###Ejercicio 1:
# Tabla de frecuencias para la variable Provincia
freq_provincia <- Freq(Andalucia$Provincia)
# Tabla de frecuencias para la variable PrincipalProcedenciaExtran
freq_extranjeros <- Freq(Andalucia$PrincipalProcedenciaExtran)

# Mostrar los resultados
print(freq_provincia)
print(freq_extranjeros)

## A)
Mode(Andalucia$Provincia)
frecuencia<-table(Andalucia$Provincia)
Minimo<-names(frecuencia[frecuencia==min(frecuencia)])
#Mas: Granada
#Menos: Cadiz
##
masdel100<-names(frecuencia[frecuencia>=100])
#Almeria, Granada, Málaga y Sevills
## C
frecuencia2<-table(Andalucia$PrincipalProcedenciaExtran)
Moda<-names(frecuencia2[frecuencia2==max(frecuencia2)])
print(Moda)
tabla[21,]

## D
barplot(frecuencia2,beside=TRUE,col=c("blue","green","pink","red"))
etiquetas<-paste(names(frecuencia),names(frecuencia2),sep=":")
pie(frecuencia2,
    main="Grafico de sectores de Nacionalidad en cada provindica",labels=etiquetas)

### Ejercicio 2: Descripción de variables cuantitativas
tabla3<-data.frame(
  Provincia=names(table(Andalucia$Altitud19)),
  ni=as.vector(table(Andalucia$Altitud19)),
  Ni=cumsum(as.vector(table(Andalucia$Altitud19))),
  fi=as.vector(prop.table(table(Andalucia$Altitud19))),
  Fi=cumsum(as.vector(prop.table(table(Andalucia$Altitud19))))
)

summary(Andalucia$Altitud19)

media_andalucia<-mean(Andalucia$Altitud19,na.rm=TRUE)
media_provincias<-aggregate(Altitud19 ~ Provincia, data=Andalucia,FUN=mean, na.rm=TRUE)

print(media_andalucia)
print(media_provincias)

media_provincias[media_provincias$Altitud19 > media_andalucia, ]

desv_provincias <- aggregate(Altitud19 ~ Provincia, data=Andalucia, FUN=sd, na.rm=TRUE)
desv_provincias[which.min(desv_provincias$Altitud9)]
library(DescTools)
## A)¿Cuál es la altitud media de los municipios de Andalucia? ¿Cuál es la 
##altitud media de los municipiosde cada provincia? ¿Qué provincias tienen una 
##altitud media superior a la media de los municipios deAndalucía?
  
