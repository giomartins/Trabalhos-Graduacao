rm(list = ls())

# Implementacao da Funcao
trainPerceptron <- function(xin, yd, eta, tol, maxEpocas, par) {
  dimXin <- dim(xin)
  N <- dimXin[1]
  n <- dimXin[2]
  
  if(par == 1) {
    wt <- as.matrix(runif(n + 1) - 0.5)
    xin <- cbind(-1, xin)
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
      yHat <- 1.0 * ((xin[iRand,] %*% wt) >= 0)
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

# Treinamento
n <- 2
N <- 30

xc1 <- matrix(rnorm(60, sd = 0.5), ncol = n, nrow = N) + matrix(c(2,2), ncol = n, nrow = N, byrow = T)
xc2 <- matrix(rnorm(60, sd = 0.5), ncol = n, nrow = N) + matrix(c(4,4), ncol = n, nrow = N, byrow = T)

plot(xc1[,1], xc1[,2], col = 'red', xlim = c(0,6), ylim = c(0,6))
par(new = T)
plot(xc2[,1], xc2[,2], col = 'blue', xlim = c(0,6), ylim = c(0,6))

xall <- rbind(xc1, xc2)
yall <- rbind(matrix(0, nrow = N), matrix(1, nrow = N))


retlist <- trainPerceptron(xall, yall, 0.001, 0.01, 1000, 1)

wfinal <-as.matrix(retlist[[1]])
plot(retlist[[2]], type = 'l')

(sign(cbind(-1, xall) %*% wfinal)+1) / 2

xrange <- cbind(seq(0, 10, 0.1), seq(0, 10, 0.1), 1)
y <- cbind(xall, -1) %*% wfinal

reta <- -(wfinal[3] / wfinal[2])*xrange + (wfinal[1]/wfinal[2])

plot(xrange, reta, xlim=c(0,6), ylim=c(0,6), xlab='', ylab='', type='l')
par(new=T)
plot(xc1[,1], xc1[,2], col='red', xlim=c(0,6), ylim=c(0,6), xlab='x', ylab='y')
par(new = T)
plot(xc2[,1], xc2[,2], col='blue', xlim=c(0,6), ylim=c(0,6), xlab='x', ylab='y')

seqx1x2 <- seq(0, 6, 0.1)
lseq <- length(seqx1x2)
MZ <- matrix(nrow = lseq, ncol = lseq)
cr <- 0

for(i in 1:lseq) {
  for(j in 1:lseq) {
    cr <- cr + 1
    x1 <- seqx1x2[i]
    x2 <- seqx1x2[j]
    x1x2 <- as.matrix((cbind(-1, x2, x1)))
    u <- (x1x2 %*% wfinal)
    MZ[i,j] <- 2 * (sign(u) + 1)
  }
}

image((MZ))
persp(seqx1x2, seqx1x2, MZ)