#Ejercicio 1
#-----------

practica2_1 <- practica2[,c(1,2)]
write.csv(practica2_1, file = "practica2_1.csv")

#Ejercicio 2
#-----------

#Modificamos el nombre de cuatro variables más a modo de ejemplo
names(practica2)[c(9, 10, 11, 12)] <- c("PobHombres23", "PobNucleos23", "PobDiseminados23", "EdadMedia22")
write.table(practica2, file = "practica2_2.txt", sep=";", row.names = FALSE)

#Ejercicio 3
#-----------

practica2$TasaMujeres23 <- (practica2$Poblacion23 - practica2$PobHombres23) / practica2$Poblacion23
writexl::write_xlsx(practica2, path = "practica2_3.xlsx")

#Ejercicio 4
#-----------

practica2_4 <- practica2[practica2$Provincia == "Jaén", c("Municipio", "Extension19", "Perimetro19", "Altitud19", "DistanciaCapital19", "Poblacion23", "EdadMedia22")]
writexl::write_xlsx(practica2_4, path = "practica2_4.xlsx")

#Ejercicio 5
#-----------

practica2_4 <- read_excel("practica2_4.xlsx")
practica2_4[practica2_4$Altitud19 > 850,]$EdadMedia22

#Ejercicio 6
#-----------

practica2$`Principal procedencia de los extranjeros residentes. 2022`
#Hay valores faltantes que aparecen con "se" y "-"
practica2$`Principal procedencia de los extranjeros residentes. 2022` <- as.numeric(practica2$`Principal procedencia de los extranjeros residentes. 2022`)

#Ejercicio 7
#-----------

practica2$`Renta disponible media. 2022`
#Al haber datos faltantes con "-", la variable es de tipo carácter
practica2$`Renta disponible media. 2022` <- as.numeric(practica2$`Renta disponible media. 2022`)
practica2$`Renta disponible media. 2022`[is.na(practica2$`Renta disponible media. 2022`)] = median(practica2$`Renta disponible media. 2022`, na.rm = TRUE)

#Ejercicio 8
#-----------

practica2$Renta22<-recode(practica2$`Renta disponible media. 2022`, 
                          "0:14999.99='Menos de 15000'; 
                          15000:19999.99='Entre 15000 y menos 20000' ; 
                          20000:24999.99='Entre 20000 y menos 25000' ; 
                          25000:29999.99='Entre 25000 y menos 30000'; 
                          30000:9999999999='30000 o superior'")

#Ejercicio 9
#-----------

save.image("practica2.RData")