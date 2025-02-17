#1. Importe el fichero de datos practica2.xlsx y genere un nuevo conjunto de datos 
#llamado practica2_1 que solo contenga las variables codMun y Municipio. Exporte 
#el conjunto de datos a un fichero llamado practica2_1.csv con cabeceras.

library(readxl)
library(writexl)

# Seleccionar solo las columnas codMun y Municipio
practica2_1 <- practica2[, c("CodMun", "Municipio")]

#2.Visualice los datos importados inicialmente. Cambie el nombre de todas las 
#variables por uno más corto. Exporte los datos a un fichero de texto llamado 
#practica2_2.txt utilizando como separador ;

str(practica2)
names(practica2)[c(3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27)]<-c("Extension","Perimetro","Altitud","Num_nucleos","Dist_capt","Pob_total","Pob_homb","Pob_nucleos","Pob_diseminados","Edad_media","%<20","%<65","Var_rel_de_poblacion","Num_extr","Emigraciones","Inmigraciones","Nacimientos","Defunciones","Matrimonios","Alcaldia","Hoteles","Hostal_pension","desempleo_municipal","Renta_bruta","Renta_disponible")

#3.Genere una nueva variable TasaMujeres23 a partir de Poblacion23 y Población. 
#Hombres. 2023. Almacene los datos resultantes con las últimas modificaciones 
#en un fichero EXCEL llamado practica2_4.xlsx.

practica2$TasaMujeres23<-(practica2$Pob_total-practica2$Pob_homb)/practica2$Pob_total

#4.Cree un nuevo conjunto de datos que contenga los municipios de Jaén y las 
#variables Municipio, Extension19, Perimetro19, Altitud19, DistanciaCapital19, 
#Poblacion23, EdadMedia22). Almacénalo en un fichero EXCEL llamado practica2_5.xlsx.

Jaen_Municipios <- practica2[practica2$CodMun >= 23001 & practica2$CodMun <= 23009, ]

