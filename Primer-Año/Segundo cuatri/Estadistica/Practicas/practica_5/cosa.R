getwd()
load("Comunicaciones.RData")

#
datos_cordoba<-Comunicaciones[Comunicaciones$Provincia == "Córdoba", ]
datos_sevilla<-Comunicaciones[Comunicaciones$Provincia == "Sevilla", ]

var.test(datos_cordoba$Veloc1GBPS, datos_sevilla$Veloc1GBPS, 
         ratio = 1, 
         alternative = "two.sided",
         conf.level = 0.95)
# contraste varianza
# 0.2811 > 0.10 No rechazo la hipotesis nula, por tanto las varianzas son iguales

t.test(datos_cordoba$Veloc1GBPS, datos_sevilla$Veloc1GBPS, 
       alternative = "two.sided",
       mu = 0, 
       paired = FALSE, 
       var.equal = TRUE,
       conf.level = 0.95)
# diferencia de media
# tipo =  two.sided
# 0.004788 < 0.1 rechazo la hipotesis, las medias son distintas
# t=-2.9247 valor estadístico de contraste

# ---------------------------------------------------------------
# 1
# Binomial
datos_malaga<-Comunicaciones[Comunicaciones$Provincia == "Málaga", ]
datos_malaga
total_malaga<-length(datos_malaga$tasa.ADSL)
menor_10<-length(datos_malaga[datos_malaga$tasa.ADSL<10,])
menor_10
prop.test(menor_10, total_malaga, 0.2, alternative = "two.side",conf.level = 0.99)

# 4.623e-10 rechazo la nula, es diferente del 20%
# 2
t.test(datos_malaga$tasa.ADSL , 
       alternative = "two.sided",
       mu = 12, 
       paired = FALSE, 
       conf.level = 0.99)
# 0.1603 > 0.01 no rechazo la hipotesis igual al 12%

#----------------------------------------------------
datos_granada=Comunicaciones[Comunicaciones$Provincia == "Granada", ]
datos_granada

cor(datos_granada$Poblacion,datos_granada$RDSI, method = "pearson")
plot(datos_granada$Poblacion,datos_granada$RDSI)




