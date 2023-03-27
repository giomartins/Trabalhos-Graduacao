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

# Problema Univariado
N <- 20
xt <- matrix(runif(N , 0, 10), ncol = 1)
yt <- (3 * xt + 5) + matrix(rnorm(N), ncol = 1)

plot(xt, yt)

retlist <- trainAdaline(xt, yt, 0.001, 0.05, 1000, 1)

evec <- retlist[[2]]
plot(evec[1:10], type = 'l')
wfinal <- retlist[[1]]

plot(retlist[[2]])

xrange <- cbind(1, seq(0,10,0.1))
yrange <- xrange %*% wfinal

plot(xt, yt, xlim = c(0,10), ylim = c(0,25))
par(new = T)
plot(xrange[,2], yrange, type='l', xlim = c(0,10), ylim = c(0,25))