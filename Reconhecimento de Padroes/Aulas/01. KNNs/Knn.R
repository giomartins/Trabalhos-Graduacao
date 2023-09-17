rm(list = ls());

# k é 
ourKNN <- function(xTeste, xin, yin, k){
    #byrow faz o preenchimento por linha
    xRepete <- matrix(xTeste, byrow=T, nrow = dim(xin)[1], ncol = dim(xin)[2])
    dmat1 <- rowSums((xRepete - xin)*(xRepete - xin))
  
    # matriz1 %*% matriz2 -> símbolo para multiplicação de matriz
    # matriz1 * matriz2 -> multiplicação elemento a elemento, ou seja, eleva ao quadrado cada elemento

    seqNN <- order(dmat1)
    yhat <- sign(sum(y[seqNN[1:k]]))
    return(yhat)
}

ourKNNponderado <- function(xt, xin, yin, k, h){
    xrep <- matrix(xt, byrow = T, nrow = dim(xin)[1], ncol = dim(xin)[2])
    
    dmat1 <- data.matrix(rowSums((xrep - xin) * (xrep - xin)))
    seqNN <- order(dmat1)
    Yknn <- yin[seqNN[1:k]]
    
    xx <- exp(-dmat1[seqNN[1:k]] / h^2)
    yhat <- sign(sum(Yknn * xx))
    
    return(yhat)
}


N1 <- 30
xc1 <- matrix(rnorm(N1*2,sd=1.2),ncol = 2, nrow = N1)+matrix(c(2,2),ncol=2,nrow = N1)

N2 <- 30
xc2 <- matrix(rnorm(N1*2,sd=1.2),ncol = 2, nrow = N1)+matrix(c(4,4),ncol=2,nrow = N2)

#xlim e ylim são os limites do gráfico, que faz ser exibido de 0 até 6
plot(xc1[,1],xc1[,2],col='red', xlim = c(0,6), ylim = c(0,6))
par(new=T)
plot(xc2[,1],xc2[,2],col='blue', xlim = c(0,6), ylim = c(0,6))

#Juntando as duas matrizes em uma só agora
x <- rbind(xc1,xc2)
# criamos uma matrix de -1 e 1
y <- rbind(matrix(-1,ncol = 1, nrow = N1), matrix(1,ncol = 1, nrow = N2))

# esse 'T' é de True, o dmat é distancia 'mat'
dmat <- data.matrix(dist(x,method = "euclidean", diag = T, upper = T)) 

persp(seq(1:60), seq(1:60), dmat, phi = 90)

image(dmat)

xTeste <- x[32,]

yhat <- ourKNN(xTeste,x,y,3)

