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

# Caso 3: mlbench.circle

circle = mlbench.circle(100)
circle = cbind(circle[[1]], circle[[2]])
circle[,3] = (circle[,3] -1.5) * 2

circleall <- splitForTrainingAndTest(circle[,1:2], circle[,3], ratio = 0.3)
xin_circle <- circleall$inputsTrain
yd_circle <- circleall$targetsTrain
xin_test_circle <- circleall$inputsTest
yteste <- circleall$targetsTest

pvet <- seq(5, 30, 5)

for(pfor in pvet){
  retlist <- treinaELM(xin_circle, yd_circle, pfor, 1)
  W_circle <- retlist[[1]]
  H_circle <- retlist[[2]]
  Z_circle <- retlist[[3]]
  yt_circle <- YELM(xin_test_circle, Z_circle, W_circle, 1)
  
  plot(circle, xlim = c(-1,1), ylim = c(-1,1))
  
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
      M[ci,cj] <- YELM(X, Z_circle, W_circle, 1)
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
    if(circle[i,3] == 1)
      points(circle[i,1], circle[i,2], col = "blue")
    if(circle[i,3] == -1)
      points(circle[i,1], circle[i,2], col = "red")
  }
}