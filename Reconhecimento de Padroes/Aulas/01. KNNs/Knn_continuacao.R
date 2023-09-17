rm(list = ls())

ourKNNponderado <- function(xt, xin, yin, k, h){
    xrep <- matrix(xt, byrow = T, nrow = dim(xin)[1], ncol = dim(xin)[2])
    
    dmat1 <- data.matrix(rowSums((xrep - xin) * (xrep - xin)))
    seqNN <- order(dmat1)
    Yknn <- yin[seqNN[1:k]]
    
    xx <- exp(-dmat1[seqNN[1:k]] / h^2)
    yhat <- sign(sum(Yknn * xx))
    
    return(yhat)
}

N <- 3000

x <- matrix(rnorm(N, sd = 0.7, mean = 4))
y <- matrix(0, nrow = N, ncol = 1)
xrange <- seq(2, 6, 0.1)
h <- 0.1
px <- matrix(ncol = 1, nrow = length(xrange))

for (i in 1:length(xrange)){
    x1 <- xrange[i]
    acc <- 0
    for (j in 1:length(x)){
        acc <- acc + exp(-((x1 - x[j])^2) / h^2)
    }
    px[i] <- acc/length(x)
}



plot(x, y, xlim = c(2,6), ylim = c(0,0.3))
par(new = T)
plot(xrange, px, type = 'l', xlim = c(2,6), ylim = c(0,0.3))
