# Limpeza de Ambiente e Importacao de Pacote para o calculo da matriz pseudoinversa
rm(list = ls())
library('corpcor')

fgx <- function(xin) 0.5*xin^2+ 3*xin + 10      # Funcao geradora fg(x)
X <- runif(n = 20, min = -15, max = 10)         # Amostra X
Y <- fgx(X) + 10*rnorm(length(X))               # Amostra Y
H <- cbind(X^2, X, 1)
W <- pseudoinverse(H) %*% Y

print(cbind(W, c(0.5, 3, 10)))                  # Comparacao dos coeficientes obtidos com os esperados

xgrid <- seq(-15, 10, 0.1)
ygrid <- (0.5*xgrid^2 + 3*xgrid + 10)           # Aplicacao de xgrid na funcao geradora
Hgrid <- cbind(xgrid^2, xgrid, 1)               
yhatgrid <- Hgrid %*% W                         # Aproximacao final obtida

# Plotagem dos resultados
plot(X, Y, type ='p', col='red', xlim=c(-15,10), ylim=c(-10, 120), xlab='x', ylab='y')
par(new=T)
plot(xgrid, ygrid, type='l', col='blue', xlim=c(-15,10), ylim=c(-10, 120), xlab='', ylab='')
par(new=T)
plot(xgrid, yhatgrid, type='l', col='green', xlim=c(-15,10), ylim=c(-10,120), xlab='', ylab='')