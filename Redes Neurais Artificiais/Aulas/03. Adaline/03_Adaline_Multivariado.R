# Implementacao da funcao de treinamento Adaline

rm(list = ls())

trainAdaline <- function(xin, yd, eta, tol, maxEpocas, par) {
  dimXin <- dim(xin)
  N <- dimXin[1]
  n <- dimXin[2]
  
  if(par == 1) {
    wt <- as.matrix(runif(n + 1) - 0.5)
    xin <- cbind(1, xin)
  } else {
    wt <- as.matrix(runif(n) - 0.5)
  }
  
  nEpocas <- 0
  eEpoca <- tol + 1
  evec <- matrix(nrow = 1, ncol = maxEpocas)
  
  while ((nEpocas < maxEpocas) && (eEpoca > tol)) {
    ei2 <- 0
    xSeq <- sample(N)
    
    for(i in 1:N) {
      iRand <- xSeq[i]
      yHat <- 1.0 * ((xin[iRand,] %*% wt))
      ei <- yd[iRand] - yHat
      dw <- eta * ei * xin[iRand,]
      wt <- wt + dw
      ei2 <- ei2 + ei * ei
    }
    
    nEpocas <- nEpocas + 1
    evec[nEpocas] <- ei2 / N
    eEpoca <- evec[nEpocas]
  }
  
  retList <- list(wt, evec[1:nEpocas])
  return(retList)
}

# Problema multivariado

t <- seq(0, 2 * pi, 0.1 * pi)
x1 <- matrix(sin(t)+cos(t), ncol = 1)
x2 <- matrix(tanh(t), ncol = 1)
x3 <- matrix(sin(4 * t), ncol = 1)
x4 <- matrix(abs(sin(t)), ncol = 1)

y <- x1 + 2*x2 + 0.8*x3 + 3.2*x4 + pi/2
x <- cbind(x1, x2, x3, x4)
retlist <- trainAdaline(x, y, 0.01, 0.01, 50, 1)

w <- retlist[[1]]
ttest <- seq(0, 2*pi, 0.01*pi)
x1t <- matrix(sin(ttest) + cos(ttest), ncol = 1)
x2t <- matrix(tanh(ttest), ncol = 1)
x3t <- matrix(sin(4*ttest), ncol = 1)
x4t <- matrix(abs(sin(ttest)), ncol = 1)
xt <- cbind(1, x1t, x2t, x3t, x4t)

yt <- xt %*% w
yreal <- 3.2*x4t + 0.8*x3t + 2*x2t + x1t + pi/2

plot(t, y, col='red', xlim=c(0,6), ylim = c(0,10), xlab='t', ylab='Saida')
par(new = T)
plot(ttest, yreal,xlab = '', ylab = '', type = 'l', col='blue', xlim=c(0,6), ylim = c(0,10))
par(new = T)
plot(ttest, yt,  xlab = '', ylab = '', type = 'l', col='green', xlim=c(0,6), ylim = c(0,10))