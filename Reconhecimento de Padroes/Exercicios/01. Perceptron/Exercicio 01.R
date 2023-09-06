# Limpeza do Ambiente
rm(list = ls())

# Função de treinamento do Perceptron:
trainPerceptron <- function(xin, yd, eta, tol, maxEpocas, par){
    N <- dim(xin)[1]    # Recebe as linhas
    n <- dim(xin)[2]    # Recebe as colunas
    
    if (par == 1) {
        wt <- as.matrix(runif(n + 1) - 0.5)     # Inicialização dos pesos
        xin <- cbind(-1, xin)
    } else {
        wt <- as.matrix(runif(n) - 0.5)         # Inicialzacao dos pesos
    }
    
    nEpocas <- 0    # Contador de épocas
    eEpoca <- tol + 1   # Acumulador de erro por epoca  
    evec <- matrix(nrow = 1, ncol = maxEpocas)  # Inicializacao do vetor erro evec
    
    # Laço de treinamento
    while((nEpocas < maxEpocas) && (eEpoca > tol)){
        ei2 <- 0
        # Sequência aleatória de treinamento
        xSeq <- sample(N)
        for (i in 1:N){
            # Amostra de dado da sequência aleatória
            iRand <- xSeq[i]
            # Calculo da saída do Perceptron
            yHat <- 1.0 * ((xin[iRand,] %*% wt) >= 0)
            ei <- yd[iRand] - yHat
            dw <- eta * ei * xin[iRand,]    # deltaW = n * e * x
            # Ajuste dos pesos
            wt <- wt + dw
            # Erro acumulado por época
            ei2 <- ei2 + (ei * ei)
        }
        # Incremento do número de épocas
        nEpocas <- nEpocas + 1
        evec[nEpocas] <- ei2 / N
        # Armazena erro por época
        eEpoca <- evec[nEpocas]
    }
    # Retorno dos vetor com os pesos e erros
    retList <- list(wt, evec[1:nEpocas])
    return(retList)
}

# Função de saida do Perceptron
yPerceptron <- function(x, w, par){
    if(par == 1){
        x <- cbind(1, x)
    }
    u <- x %*% w
    y <- 1.0 * (u >= 0)
    return(as.matrix(y))
}

# Declaração dos conjuntos de entrada e plotagem dos dados
sd1 <- 0.4
sd2 <- 0.4
tam <- 200

xc1 <- matrix(rnorm(tam * 2), ncol = 2) * sd1 + t(matrix(c(2,2), ncol = tam, nrow = 2))
xc2 <- matrix(rnorm(tam * 2), ncol = 2) * sd2 + t(matrix(c(4,4), ncol = tam, nrow = 2))

plot(xc1[,1], xc1[,2], col = "red", xlim = c(0,6), ylim = c(0,6), xlab = "x_1", ylab = "x_2")
par(new = T)
plot(xc2[,1], xc2[,2], col = "blue", xlim = c(0,6), ylim = c(0,6), xlab = "x_1", ylab = "x_2")

x1_reta <- seq(6/100, 6, 6/100)
x2_reta <- (-x1_reta) + 6

par(new = T)
plot(x1_reta, x2_reta, type = "l", col = "orange", xlim = c(0,6), ylim = c(0,6), xlab = "x_1", ylab = "x_2")


# Treinamento e Classificação do Perceptron
xc1 <- cbind(xc1, 0)
xc2 <- cbind(xc2, 1)
x <- rbind(xc1, xc2)
retlist <- trainPerceptron(x[, 1:2], x[,3], 0.1, 0.01, 100, 1)
#w <- matrix(retlist[[1]])
w <- retlist[[1]]

seqi <- seq(0, 6, 0.1)
seqj <- seq(0, 6, 0.1)
rt <- matrix(0, nrow = length(seqi), ncol = length(seqj))
ci <- 0

for (i in seqi) {
    ci <- ci + 1
    cj <- 0
    for (j in seqj) {
        cj <- cj + 1
        #x <- as.matrix(t(c(1, i, j)))  # Adicione 1 para o termo de polarização
        x <- as.matrix(t(c(i,j)))
        rt[ci, cj] <- yPerceptron(x, w, 1)
    }
}


# Plote os pontos das classes
plot(xc1[,1], xc1[,2], col = 'red', xlim = c(0,6), ylim = c(0,6), xlab = 'x_1', ylab = 'x_2')
par(new = T)
plot(xc2[,1], xc2[,2], col = 'blue', xlim = c(0,6), ylim = c(0,6), xlab = 'x_1', ylab = 'x_2')
par(new = T)

# Plote a reta de separação usando contour com os níveis corretos
contour(seqi, seqj, rt, xlim = c(0,6), ylim = c(0,6), xlab = '', ylab = '')

