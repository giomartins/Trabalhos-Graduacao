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

# Caso 4: mlbench.spiral

espiral = as.matrix(mlbench.spirals(100, 1, sd = 0.05))
espiral = cbind(espiral[[1]], espiral[[2]])
espiral[,3] = (espiral[,3]-1.5) * 2

espiralall <- splitForTrainingAndTest(espiral[,1:2], espiral[,3], ratio = 0.1)
xin_espiral <- espiralall$inputsTrain
yd_espiral <- espiralall$targetsTrain
xin_test_espiral <- espiralall$inputsTest
yteste <- espiralall$targetsTest

pvet <- seq(5, 30, 5)

for(pfor in pvet) {
  retlist <- treinaELM(xin_espiral, yd_espiral, pfor, 1)
  W_espiral <- retlist[[1]]
  H_espiral <- retlist[[2]]
  Z_espiral <- retlist[[3]]
  yt_espiral <- YELM(xin_test_espiral, Z_espiral, W_espiral, 1)
  
  plot(espiral, xlim = c(-1,1), ylim = c(-1,1))
  
  seqi <- seq(-1, 1, 0.05)
  seqj <- seq(-1, 1, 0.05)
  M <- matrix(0, nrow = length(seqi), ncol = length(seqj))
  ci <- 0
  
  for(i in seqi){
    ci <- ci + 1
    cj <- 0
    for(j in seqj){
      cj <- cj + 1
      X <- as.matrix(t(c(i,j)))
      M[ci,cj] <- YELM(X, Z_espiral, W_espiral, 1)
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
    if(espiral[i,3] == 1)
      points(espiral[i,1], espiral[i,2], col = "blue")
    if(espiral[i,3] == -1)
      points(espiral[i,1], espiral[i,2], col = "red")
  }
}