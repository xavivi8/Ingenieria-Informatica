###Ejercicio 1: Descripción de variables cualitativas
###Contruya la tabla de frecuencias y represente los gráficos 
###apropiados para los datos de las variables Provinciay PrincipalProcedenciaExtran. 
###A partir de los resultados, responda a las siguientes preguntas:

##A) ¿Cuál es la provincia con más municipios? ¿Y con menos?-------------------
#Se encuentra facil en las diapositivas (Practica 3: Página 1)
tabla_municipios_provincias = table(Andalucia$Provincia)
tabla_municipios_provincias
# -----------
#Mas: Granada
#Menos: Cadiz
# -----------
##B) ¿Qué provincias tienen más de 100 municipios?------------------------------
#No sale en las diapositivas, hay que aprenderse la estructura de memoria
tabla_municipios_provincias[tabla_municipios_provincias>100]
names(tabla_municipios_provincias[tabla_municipios_provincias>100])
# -----------
#Almeria, Granada, Málaga y Sevills
# -----------
##C) ¿Qué nacionalidad extranjera es la principal en los municipios de 
##Andalucía? ¿De qué medida se trata? ¿Cuál es su proporción sobre el total?
#Se encuentra facil en las diapositivas (Practica 3: Página 1)
tabla_extrajeros_absoluta<-table(Andalucia$PrincipalProcedenciaExtran)
tabla_extrajeros_relativa<-prop.table(tabla_extrajeros_absoluta)
tabla_extrajeros_absoluta
tabla_extrajeros_relativa
# -----------
# La procedencia principal de los extranjeros en los municipios andaluces es 
# Marruecos (moda).
# Su proporción sobre el total es 0.387862797 (38.7862797%)
# -----------
##D) Genere los gráficos y tablas adecuados para contestar a la siguiente
##pregunta. ¿Cuál es la nacionalidad predominante en los municipios de cada 
##provincia?
  
barplot(frecuencia2,beside=TRUE,col=c("blue","green","pink","red"))
etiquetas<-paste(names(frecuencia),names(frecuencia2),sep=":")
pie(frecuencia2,
    main="Grafico de sectores de Nacionalidad en cada provindica",labels=etiquetas)

#Tabla de frecuencias absolutas y relativas - Facil, es copia y pega del pdf (Practica 3: paginas 1 y 2)
tablaFreq <- data.frame(Paises = names(tabla_extrajeros_absoluta),
                        ni = as.vector(tabla_extrajeros_absoluta),
                        fi = as.vector(tabla_extrajeros_relativa))
tablaFreq

#Grafico de barras - Facil, es copia y pega del pdf (Practica 3: paginas 3, 4 y 5)
barplot(tabla_extrajeros_absoluta, main = "Gráfico Barras procedencia extranjera",
        xlab = "Pais de procedencia", ylab="Frecuencia absoluta")

#Grafico de sectores - Facil, es copia y pega del pdf (Practica 3: paginas 5, 6, 7 y 8)
etiquetas = paste(names(tabla_extrajeros_absoluta), tabla_extrajeros_absoluta, sep=": ")
pie(tabla_extrajeros_absoluta, main = "Gráfico de Sectores procedencia extranjeros en Andalucia", labels = etiquetas)

#Histograma (Autogenerado) - Facil, es copia y pega del pdf (Practica 3: paginas 8 y 9)
hist(tabla_extrajeros_absoluta , 
     main = "Histograma procedencia extranjeros en Andalucia",
     xlab = "Número de extranjeros",
     ylab = "Frecuencia")

#Histograma (Con intervalos personalizados) - Facil, es copia y pega del pdf (Practica 3: paginas 9 y 10)
hist(tabla_extrajeros_absoluta , breaks = seq(0,300, by=100) , 
     main = "Histograma procedencia extranjeros en Andalucia",
     xlab = "Número de extranjeros",
     ylab = "Frecuencia")

##########################################################################################################3
##########################################################################################################3
##########################################################################################################3
##########################################################################################################3
##########################################################################################################3


### Ejercicio 2: Descripción de variables cuantitativas

##2.1 Realice un estudio descriptivo de la variable Altitud19 para el conjunto 
##de los municipios de Andalucía y para los municipios de cada provincia. A 
##continuación conteste a las siguientes cuestiones:

## A)¿Cuál es la altitud media de los municipios de Andalucia? ¿Cuál es la 
##altitud media de los municipiosde cada provincia? ¿Qué provincias tienen una 
##altitud media superior a la media de los municipios deAndalucía?
#Media altitud de todos los municipios de andalucia - No sale en el pdf pero es facil, se entiende
media_altitud_municipios_andalucia=mean(Andalucia$Altitud19)
media_altitud_municipios_andalucia

#Media altitud para cada provincia de andalucia - Sale tal cual en el pdf pero 
#con otro ejemplo (Practica 3: pagina 17)
media_altitud_cada_provincia_andalucia = aggregate(Altitud19 ~ Provincia, data = Andalucia, FUN = mean)
media_altitud_cada_provincia_andalucia
# -----------
#Almería, Granada y Jaén tienen una altitud media superior a la media de 
#municipios de andalucia
# -----------
## B) ¿En qué provincia los datos sobre la altitud media de los municipios son 
##más homogéneos?
aggregate(Altitud19 ~ Provincia, data = Andalucia, FUN =
            function(x) c(media = mean(x),
                          mediana = median(x),
                          sd = sd(x),#desviación estandar
                          cv = sd(x) / mean(x)#coeficiente de variación
            )
)
# -----------
#La provincia en la que los datos sobre la altitud media de los municipios son 
#más homogéneos es en Jaén
# -----------
## C)Calcule los coeficientes de asimetría y curtosis para la variable altitud 
##en cada provincia y compárelos
library("DescTools")
aggregate(Altitud19 ~ Provincia, data = Andalucia, FUN =
            function(x) c(coef_asimetria = Skew(x),
                          coef_curtosis = Kurt(x)
            )
)
## D)¿Qué municipios andaluces destacan como atípicos sobre el resto, en cada 
##provincia, por su alta o baja altitud?
cajas <- boxplot(Altitud19~Provincia,data=Andalucia)
cajas$out
Andalucia[Andalucia$Altitud19 %in% cajas$out & Andalucia$Provincia == "Cádiz",]
Andalucia[Andalucia$Altitud19 %in% cajas$out & Andalucia$Provincia == "Granada",]
Andalucia[Andalucia$Altitud19 %in% cajas$out & Andalucia$Provincia == "Jaén",]

##2.2 . Construya una tabla de frecuencias para la variable RentaBruta en la 
##provincia de Málaga, con 9 intervalos de amplitud 3000, comenzando en 13000. 
##A partir de la tabla anterior, responda a las siguientes cuestiones:

rentaMalaga = Andalucia[Andalucia$Provincia == "Málaga", ]
rentaMalaga

intervalos_renta_malaga <- cut(rentaMalaga$RentaBruta, breaks = seq(13000, 40000, by = 3000), right = TRUE)

frec_abs_renta_malaga<-table(intervalos_renta_malaga)
frec_rel_renta_malaga<-prop.table(frec_abs_renta_malaga)

tabla_freq_renta_malaga <- data.frame(
  Intervalos = names(frec_abs_renta_malaga),
  ni = as.vector(frec_abs_renta_malaga),
  Ni = cumsum(as.vector(frec_abs_renta_malaga)),
  fi = as.vector(frec_rel_renta_malaga),
  Fi = cumsum(as.vector(frec_rel_renta_malaga))
)
tabla_freq_renta_malaga

#Esta forma de hacerlo selecciona unicamente la columna "RentaBruta" de las 
#filas que tengan "Málaga" como provincia
rentaMalaga2 <- Andalucia[Andalucia$Provincia == "Málaga", "RentaBruta"]
rentaMalaga2
intervalos_renta_malaga2 <- cut(rentaMalaga2, breaks = seq(13000, 40000, by = 3000), right = TRUE)
intervalos_renta_malaga2
frec_abs_renta_malaga2<-table(intervalos_renta_malaga2)
frec_rel_renta_malaga2<-prop.table(frec_abs_renta_malaga2)

tabla_freq_renta_malaga2 <- data.frame(
  Intervalos = names(frec_abs_renta_malaga2),
  ni = as.vector(frec_abs_renta_malaga2),
  Ni = cumsum(as.vector(frec_abs_renta_malaga2)),
  fi = as.vector(frec_rel_renta_malaga2),
  Fi = cumsum(as.vector(frec_rel_renta_malaga2))
)
tabla_freq_renta_malaga2

## A) ¿Cuántos municipios tienen una renta bruta superior a 28000€? ¿Y mayor 
##que 19000€ y menor o igual a 31000?
#Se puede hacer observando la tabla anterior, de la que deducimos que 8 
#minicipios tienen una renta superior a 28000 y 66 una renta superiora 19000 y 
#menor o igual a 31000

#Esta es otra forma más "Cutre" de hacerlo, si no tubiesemos la tabla anterior, 
#que justo tiene intervalos en los puntos donde empiezan y terminan los rangos 
#pedidos. Esta forma de hacerlo nos da directamente el número

num_municipios_28000 <- sum(rentaMalaga > 28000)
num_municipios_28000

num_municipios_19000_31000 <- sum(rentaMalaga > 19000 & rentaMalaga<=31000)
num_municipios_19000_31000
## B)¿Cuál es el intervalo de renta bruta más usual en los municipios de Málaga?

#El intervalo de renta más usaual se puede ver la tabla anterior y es el que va 
#de 19000 a 22000

##2.3 Represente el histograma para la varible RentaBruta en los municipios de 
##la provincia de Málaga, utilizando los mismos intervalos del ejercicio 
##anterior. A partir de él, ¿qué opina sobre la simetría de los datos?

rentaMalaga_solorenta <- Andalucia[Andalucia$Provincia == "Málaga", ]$RentaBruta

hist(rentaMalaga_solorenta , breaks = seq(13000, 40000, by=3000),
     main = "Histograma para procesos concurrentes",
     xlab = "Precio de la renta",
     ylab = "Frecuencia")

#Los datos son asimetricos a la derecha
  