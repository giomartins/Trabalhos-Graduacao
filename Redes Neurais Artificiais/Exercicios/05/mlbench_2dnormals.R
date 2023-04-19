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

# Caso 1: mlbench.2dnormals

normals = mlbench.2dnormals(200)
normals = cbind(normals[[1]], normals[[2]])
normals[,3] = (normals[,3] - 1.5) * 2
normalsall <- splitForTrainingAndTest(normals[,1:2], normals[,3], ratio = 0.3)

xin_normals <- normalsall$inputsTrain
yd_normals <- normalsall$targetsTrain
xin_test_normals <- normalsall$inputsTest
yteste <- normalsall$targetsTest

pvet <- seq(5, 30, 5)

for(pfor in pvet) {
  retlist <- treinaELM(xin_normals, yd_normals, pfor, 1)
  W_normals <- retlist[[1]]
  H_normals <- retlist[[2]]
  Z_normals <- retlist[[3]]
  yt_normals <- YELM(xin_test_normals, Z_normals, W_normals, 1)
  
  plot(normals, xlim = c(-3, 3), ylim = c(-4, 4))
  
  seqi <- seq(-4, 4, 0.2)
  seqj <- seq(-3, 3, 0.15)
  M <- matrix(0, nrow = length(seqi), ncol = length(seqj))
  ci <- 0
  
  for(i in seqi) {
    ci <- ci + 1
    cj <- 0
    for(j in seqj) {
      cj <- cj + 1
      X <- as.matrix(t(c(i,j)))
      M[ci,cj] <- YELM(X, Z_normals, W_normals, 1)
    }
  }
  
  for(i in 1:length(seqi)) {
    for(j in 1:length(seqj)) {
      if(M[i,j] == 1)
        points(seqj[i], seqi[j], pch = 4, col = "cornsilk3")
      else
        points(seqj[i], seqi[j], pch = 4, col = "darkseagreen1")
    }
  }
  
  for(i in 1:200) {
    if(normals[i,3] == 1)
      points(normals[i,1], normals[i,2], col = "blue")
    if(normals[i,3] == -1)
      points(normals[i, 1], normals[i,2], col = "red")
  }
}