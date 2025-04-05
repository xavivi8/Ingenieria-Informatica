#p para el menor igual y d el para igual
## Ejer 1
# a
n=200;
p=0.02
sol_1a = dbinom(5,size = n, prob = p)
cat("Probabilidad binomial P(X=5): ",sol_1a,"\n")
#b

#c
n = 200
p = 0.02
q = 1 - p
mu = n * p
sigma = sqrt(n * p * q)
x = 0:n
binom = dbinom(x, n, p)
norm = dnorm(x, mu, sigma)

plot(x, binom, type = "h", col = "blue",
     main = "Dist. binomial y aprox a la normal",
     xlab = "N de bombillas defectuosas",
     ylab = "Probabilidad",
     ylim = c(0, max(binom, norm)))
lines(x, norm, col = "red")


