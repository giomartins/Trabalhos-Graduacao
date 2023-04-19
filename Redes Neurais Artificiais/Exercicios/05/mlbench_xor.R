rm(list=ls())
library('RSNNS')
library('mlbench')

YELM <- function(xin, Z, W, par){
  n <- dim(xin)[2]
  if (par == 1)
    xin <- cbind(1, xin)
  H <- tanh(xin %*% Z)
  yhat <- sign(H %*% W)
  return(yhat)
}

treinaELM <-function(xin, yin, p, par) {
  n <- dim(xin)[2]
  if (par == 1) {
    xin <- cbind(1, xin)
    Z <- replicate(p, runif((n+1), -0.5, 0.5))
  }
  else
    Z <- replicate(p, runif((n+1), -0.5, 0.5))
  H <- tanh(xin %*% Z)
  W <- (solve(t(H) %*% H) %*% t(H)) %*% yin
  return(list(W, H, Z))
}

# Caso 2: mlbench.xor

xor = mlbench.xor(100)
xor = cbind(xor[[1]], xor[[2]])
xor[,3] = (xor[,3] -1.5) * 2

xorall <- splitForTrainingAndTest(xor[,1:2], xor[,3], ratio = 0.1)
xin_xor <- xorall$inputsTrain
yd_xor <- xorall$targetsTrain
xin_test_xor <- xorall$inputsTest
ytest <- xorall$targetsTest

pvet <- seq(5, 30, 5)

for(pfor in pvet){
  retlist <- treinaELM(xin_xor, yd_xor, pfor, 1)
  W_xor <- retlist[[1]]
  H_xor <- retlist[[2]]
  Z_xor <- retlist[[3]]
  yt_xor <- YELM(xin_test_xor, Z_xor, W_xor, 1)
  
  plot(xor, xlim = c(-1, 1), ylim = c(-1,1))
  
  seqi <- seq(-1, 1, 0.05)
  seqj <- seq(-1, 1, 0.05)
  M <- matrix(0, nrow = length(seqi), ncol = length(seqj))
  ci <- 0
  
  for(i in seqi){
    ci <- ci + 1
    cj <- 0
    for(j in seqj){
      cj <- cj + 1
      X <- as.matrix(t(c(i, j)))
      M[ci, cj] <- YELM(X, Z_xor, W_xor, 1)
    }
  }
  
  for(i in 1:length(seqi)){
    for(j in 1:length(seqj)){
      if(M[i,j] == 1)
        points(seqj[i], seqi[j], pch = 4, col = "cornsilk3")
      else
        points(seqj[i], seqi[j], pch = 4, col = "darkseagreen1")
    }
  }
  
  for(i in 1:100){
    if(xor[i,3] == 1)
      points(xor[i,1], xor[i,2], col = "blue")
    if(xor[i,3] == -1)
      points(xor[i,1], xor[i,2], col = "red")
  }
}