rm(list = ls())
library('RSNNS')

normalize <- function(x) {
  return((x - min(x)) / (max(x) - min(x)))
}

# Carregando a base de dados
housing_data <- read.table("C:/Projetos/Trabalhos-Faculdade/Redes Neurais Artificiais/Exercicios/10/housing.data", quote="\"", comment.char="")
colnames(housing_data) <- c("CRIM", "ZN", "INDUS", "CHAS", "NOX", "RM", "AGE", "DIS", "RAD", "TAX", "PTRATIO", "B", "LSTAT", "MEDV")

# Separando os dados de entrada e saida do dataset
X <- housing_data[,1:13]
Y <- housing_data[, 14]

# Divisao dos dados em treinamento e teste
set.seed(123)
training_index <- sample(1:nrow(housing_data), 0.7 * nrow(housing_data))
test_index <- setdiff(1:nrow(housing_data), training_index)

X_training <- X[training_index,]
X_test <- X[test_index,]
Y_training <- Y[training_index]
Y_test <- Y[test_index]

# Normalizacao dos dados de entrada
X_training <- apply(X_training, 2, normalize)
X_test <- apply(X_test, 2, normalize)


# Montagem da arquitetura
number_neurons <- c(10, 30, 50) # Numero de neuronios em cada camada oculta

for (n in number_neurons) {
  model <-  mlp (X_training, Y_training, size=c(n), maxit=20000, initFunc="Randomize_Weights", initFuncParams=c(-5, 5),
                 learnFunc="Std_Backpropagation", learnFuncParams=c(0.001, 0.5), 
                 updateFunc="Topological_Order", updateFuncParams=c(0),
                 hiddenActFunc="Act_Logistic", 
                 shufflePatterns=TRUE, linOut=TRUE) 
  
  # Previsao do conjunto de teste
  Y_prediction <- predict(model, X_test)
  
  # Calculo do erro medio e do desvio padrao
  Error <- Y_prediction - Y_test
  Mean_Error <- mean(Error)
  SD_Error <- sd(Error)
  
  # Resultados
  cat("Numero de Neuronios: ", n, "\n")
  cat("Erro Medio: ", Mean_Error, "\n")
  cat("Desvio Padrao: ", SD_Error, "\n\n")
}