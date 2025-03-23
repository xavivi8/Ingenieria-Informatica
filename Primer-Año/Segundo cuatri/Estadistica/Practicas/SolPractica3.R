# -----------
# EJERCICIO 1
# -----------

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

# Apartado a)
# -----------

# Granada (moda) y Cádiz

# Apartado b)
# -----------

tablaFrec.provincia[tablaFrec.provincia$ni > 100, 1]
# [1] "Almería" "Granada" "Málaga"  "Sevilla"

# Apartado c)
# -----------

# La procedencia principal de los extranjeros en los municipios andaluces es 
# Marruecos (moda).
# Su proporción sobre el total es 0.387862797 (38.7862797%)

# Apartado d)
# -----------

# Hacemos una tabla de frecuencias para cada provincia

# Almeria
Almeria <- Andalucia[Andalucia$Provincia == "Almería",] # Filtramos los datos de Almería

frec_abs_proc_AL <- table(Almeria$PrincipalProcedenciaExtran)

frec_abs_proc_AL

frec_rel_proc_AL <- prop.table(frec_abs_proc_AL)

frec_rel_proc_AL

tablafrec.AL.procedencia <- data.frame(procedencia = names(frec_abs_proc_AL),
                                    ni = as.vector(frec_abs_proc_AL),
                                    fi = as.vector(frec_rel_proc_AL))
tablafrec.AL.procedencia

barplot(frec_abs_proc_AL, main = "Gráfico de barras: Procedencia principal de extranjeros en Almería",
        xlab = "País", ylab="Número de municipios", 
        col = c("blue"))

# En Almería el principal país de procedencia de los extranjeros por municipios es Reino Unido.

# Repetimos el mismo proceso con las 7 provincias restantes

# -----------
# EJERCICIO 2
# -----------

# Punto 1
# -------

summary(Andalucia$Altitud19) # o simplemente mean(Andalucia$Altitud19)

aggregate(Altitud19 ~ Provincia, data = Andalucia, FUN =
            function(x) c(media = mean(x),
                          mediana = median(x),
                          var = var(x),
                          sd = sd(x),
                          cv = sd(x) / mean(x),
                          Q1 = quantile(x,0.25,type = 2),
                          Q3 = quantile(x,0.75,type = 2)))

# Apartado a)
# -----------

# La altitud media de los municipios de Andalucía es 503.2 m. 

# Almería, Granada y Jaén tienen una altitud media superior a la media andaluza.

# Apartado b) 
# -----------

# Son más homogéneos los datos sobre la altitud media en la provincia de Jaén

# Apartado c)
# -----------

# Coeficiente de asimetría de Fisher
install.packages("DescTools")
library(DescTools)
aggregate(Altitud19 ~ Provincia, data = Andalucia, FUN = function(x) Skew(x, method = 1))

# Coeficiente de curtosis de Fisher
aggregate(Altitud19 ~ Provincia, data = Andalucia, FUN = function(x) Kurt(x, method = 1))

# O ambos coeficientes a la vez
aggregate(Altitud19 ~ Provincia, data = Andalucia, FUN = 
            function(x) c(asimetria = Skew(x, method = 1), 
                          curtosis = Kurt(x, method = 1)))

# También podemos añadir estas dos medidas a la función aggregate que contiene las medidas 
# de posición y dispersión.

aggregate(Altitud19 ~ Provincia, data = Andalucia, FUN =
            function(x) c(media = mean(x),
                          mediana = median(x),
                          var = var(x),
                          sd = sd(x),
                          cv = sd(x) / mean(x),
                          Q1 = quantile(x,0.25,type = 2),
                          Q3 = quantile(x,0.75,type = 2),
                          asimetria = Skew(x, method = 1), 
                          curtosis = Kurt(x, method = 1)))

# Los datos sobre altitud que presentan asimetría a la derecha son los de las provincias de
# Almería, Cádiz, Huelva, Jaén y Sevilla.

# Son más asimétricos los datos sobre altitud correspondientes a la provincia de Cádiz y 
# menos asimétricos los datos correspondientes a la provincia de Almería.

# Son más apuntados que la distribución normal (leptocúrticos) los datos sobre la altitud 
# correspondientes a las provincias de Cádiz, Granada y Sevilla. 

# Apartado d)
# -----------

# Obtenemos los valores anómalos mediante los gráficos de caja y bigotes por provincias

cajas <- boxplot(Altitud19 ~ Provincia, data = Andalucia)

# Valores anómalos

cajas$out

# Obtenemos el listado de municipios anómalos por provincias usando %in%

Andalucia[Andalucia$Altitud19 %in% cajas$out & Andalucia$Provincia == "Cádiz",]
# Grazalema y Villaluenga del Rosario

Andalucia[Andalucia$Altitud19 %in% cajas$out & Andalucia$Provincia == "Granada",]
# Almuñecar, Gualchos, Jete, Motril, Polopos, Salobreña, Torrenueva, Trevélez y Vélez de Benaudalla

Andalucia[Andalucia$Altitud19 %in% cajas$out & Andalucia$Provincia == "Jaén",]
# Santiago-Pontones


# Punto 2
# -------

# Construimos la tabla de frecuencias agrupando en intervalos

Malaga <- Andalucia[Andalucia$Provincia == "Málaga", ]

intervalos <- cut(Malaga$RentaBruta, breaks = seq(13000, 40000, by = 3000), right = TRUE)
frec_abs_renta_MA <- table(intervalos)
frec_rel_renta_MA <- prop.table(frec_abs_renta)
tablafrec.renta.MA <- data.frame(
  intervalos = names(frec_abs_renta),
  ni = as.vector(frec_abs_renta),
  Ni = cumsum(as.vector(frec_abs_renta)),
  fi = as.vector(frec_rel_renta),
  Fi = cumsum(as.vector(frec_rel_renta))
)

tablafrec.renta.MA

# Apartado a)
# -----------

# 3 municipios de Málaga tienen una renta bruta superior a 28000€.

# 66 municipios de Málaga tienen una renta bruta mayor que 19000€ y menor o igual que 31000€.

# Apartado b)
# -----------

# El intervalo de renta bruta más usual en los municipios de Málaga es (19000€, 22000€].

# Punto 3
# -------

# Histograma para la renta bruta en la provincia de Málaga

hist(Malaga$RentaBruta, breaks = seq(13000, 40000, by = 3000),
     main = "Histograma para la renta bruta en Málaga",
     xlab = "Renta bruta",
     ylab = "Número de municipios",
     col = "red")

# Las barras más altas del histograma se sitúan a la izquierda, lo que significa que los
# datos sobre la renta bruta en la provincia de Málaga presentan asimetría a la derecha.
# Podemos comprobarlo viendo que el coeficiente de asimetría de Fisher es positivo.

Skew(Malaga$RentaBruta, method = 1)

# 1.787346