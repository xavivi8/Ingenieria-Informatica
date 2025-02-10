vect<-c(10,20,30,40,50)
length(vect)

matrix <- matrix(1:12, nrow=3,ncol=4)
dim(matrix)

data <- data.frame(
  ID=1:3,
  Name=c("Alice","Bob","Charlie"),
  Age=c(25,35,29)
)
class(data)

str(data)

colnames<-names(data)
print(colnames)

names(data)<-c("ident","nombre","Edad")
print(names(data))

sequence<-sec(from=1,to=10,by=2)
sequence

repeated<-rep(c(4,5,6),times=2)
repeated

sampled<-sample(c(1,2,3,4,5),size=3)
sampled

vect<-c(1,2,3,4,5)
sum(vect)

cumsum(vect)

cumprod(vect)

matiz<-matrix(1:9,nrow=3,ncol=3)
matrix

rowSuns(matriz)
colsSums(matrix)

vect1<-c(-3,-5,2,-8,6)

min(vect1)

mac(vect1)

num<-3.14159
round(num,digits=2)

v1<-c(1,2,3)
v2<-c(4,5,6)

cbind(v1,v2)
data<-data.frame(
  ID=1:5,
  Score=c(50,75,42,83,66)
)
subset(data,Score>60)

data1 <-data.frame(
  ID=c(1,2,3),
  Name=c("Alice","Bob",Charlie)
)

data2 <-data.frame(
  ID=c(1,2,4),
  Age=c(23,45,33)
)

merge(data1,data2,by="ID")

vect4<.c(TRUE,TRUE,FALSE)
ifelse(vect>6,"Alta","Baja")