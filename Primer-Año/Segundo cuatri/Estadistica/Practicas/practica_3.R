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

###Ejercicio 1: Descripción de variables cualitativas
###Contruya la tabla de frecuencias y represente los gráficos 
###apropiados para los datos de las variables Provinciay PrincipalProcedenciaExtran. 
###A partir de los resultados, responda a las siguientes preguntas:
# Tabla de frecuencias para la variable cualitativa "Provincia"

frec_abs_prov <- table(Andalucia$Provincia)

frec_abs_prov

frec_rel_prov <- prop.table(frec_abs_prov) 

frec_rel_prov

tablafrec.provincia <- data.frame(provincias = names(frec_abs_prov),
                                  ni = as.vector(frec_abs_prov),
                                  fi = as.vector(frec_rel_prov))
tablafrec.provincia

# Tabla de frecuencias para la variable cualitativa "PrincipalProcedenciaExtran"

frec_abs_proc <- table(Andalucia$PrincipalProcedenciaExtran)

frec_abs_proc

frec_rel_proc <- prop.table(frec_abs_proc)

frec_rel_proc

tablafrec.procedencia <- data.frame(procedencia = names(frec_abs_proc),
                                    ni = as.vector(frec_abs_proc),
                                    fi = as.vector(frec_rel_proc))
tablafrec.procedencia

# Gráfico de barras para la variable cualitativa "Provincia"

barplot(frec_abs_prov, main = "Gráfico de barras: Provincias de Andalucía",
        xlab = "Provincia", ylab="Número de municipios", 
        col = c("red", "blue", "green", "yellow","orange","purple", "pink", "gray"))


# Gráfico de sectores para la variable cualitativa "Provincia"

etiquetas = paste(names(frec_abs_prov), frec_abs_prov, sep=": ")

pie(frec_abs_prov, main = "Gráfico de sectores: Provincias de Andalucía",
    xlab = "Provincia", ylab="Número de municipios", 
    col = c("red", "blue", "green", "yellow","orange","purple", "pink", "gray"),
    labels = etiquetas)

# Gráfico de barras para la variable cualitativa "PrincipalProcedenciaExtran"

barplot(frec_abs_proc, main = "Gráfico de barras: Procedencia principal de extranjeros en Andalucía",
        xlab = "País", ylab="Número de municipios", 
        col = c("red"))

# Gráfico de sectores para la variable cualitativa "PrincipalProcedenciaExtran"

pie(frec_abs_proc, main = "Gráfico de sectores: Procedencia principal de extranjeros",
    xlab = "País", ylab="Número de municipios", 
    col = c("red", "blue", "green", "yellow","orange","purple", "pink", "gray"))

## A) ¿Cuál es la provincia con más municipios? ¿Y con menos?-------------------
Mode(Andalucia$Provincia)
frecuencia<-table(Andalucia$Provincia)
Minimo<-names(frecuencia[frecuencia==min(frecuencia)])
# -----------
#Mas: Granada
#Menos: Cadiz
# -----------
##B) ¿Qué provincias tienen más de 100 municipios?------------------------------
masdel100<-names(frecuencia[frecuencia>=100])
# -----------
#Almeria, Granada, Málaga y Sevills
# -----------
## C) ) ¿Qué nacionalidad extranjera es la principal en los municipios de 
##Andalucía? ¿De qué medida se trata? ¿Cuál es su proporción sobre el total?
  
frecuencia2<-table(Andalucia$PrincipalProcedenciaExtran)
Moda<-names(frecuencia2[frecuencia2==max(frecuencia2)])
print(Moda)
tabla[21,]

## D) Genere los gráficos y tablas adecuados para contestar a la siguiente
##pregunta. ¿Cuál es la nacionalidad predominante en los municipios de cada 
##provincia?
  
barplot(frecuencia2,beside=TRUE,col=c("blue","green","pink","red"))
etiquetas<-paste(names(frecuencia),names(frecuencia2),sep=":")
pie(frecuencia2,
    main="Grafico de sectores de Nacionalidad en cada provindica",labels=etiquetas)

##########################################################################################################3
##########################################################################################################3
##########################################################################################################3
##########################################################################################################3
##########################################################################################################3


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
coef_asimetria <- aggregate(Altitud19 ~ Provincia, data=Andalucia,FUN=function(x) Skew(x, na.rm=TRUE))
coef_curtosis <- aggregate(Altitud19 ~ Provincia,data=Andalucia,FUN=function(x) Kurt(x, na.rm=TRUE))

print(coef_asimetria)
print(coef_curtosis)

boxplot(Andalucia$Altitud19 ~ Andalucia$Provincia, main="")

## B

malaga <- subset(Andalucia, PRovincia=="Málaga")

intervalos <- seq(13000, max(malaga$RentaBruta, na.rm=TRUE), by3000)
malaga$RentaGrupo <- cut(malaga$RentaBruta, breaks=intervalos, right=TRUE)

tabla_freq <- table(malaga$RentaBruta)
tabla_freq_rel <- prop.table(tabla_freq)

## C
data.frame(Intervalo=names(tabla_freq),Frecuqncia=as.vector(tabla_freq), Relativa=as.vector(tabla_freq_rel))

sum(malaga$RentaBruta > 28000, na.rm=TRUE)
sum(malaga$RentaBruta > 19000 & malaga$RentaBruta <= 31000, na.rm=TRUE)

tabla_renta_andalucia <- table(cut(Andalucia$RentaBruta, breaks=intervalos, right=TRUE))
  
