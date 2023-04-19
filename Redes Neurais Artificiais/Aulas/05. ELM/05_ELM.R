library('plot3D')
library('corpcor')

tam_treinamento<- 1

#gerando os dados
s1<-0.2
s2<-0.2
nc<-50
xc11<-matrix(rnorm(nc*2),ncol=2)*s1 + t(matrix(c(2,2),ncol=nc, nrow=2))
xc12<-matrix(rnorm(nc*2),ncol=2)*s2 + t(matrix(c(4,4),ncol=nc, nrow=2))
xc21<-matrix(rnorm(nc*2),ncol=2)*s1 + t(matrix(c(2,4),ncol=nc, nrow=2))
xc22<-matrix(rnorm(nc*2),ncol=2)*s2 + t(matrix(c(4,2),ncol=nc, nrow=2))
xc1<-rbind(xc11,xc12)
xc2<-rbind(xc21,xc22)

#plotando os dados gerados
plot(xc1[,1],xc1[,2],col='red', xlim = c(0,6), ylim = c(0,6), xlab = 'x_1', ylab = 'x_2')
par(new=T)
plot(xc2[,1],xc2[,2],col = 'blue', xlim= c(0,6), ylim=c(0,6), xlab='', ylab = '')

#Organizando os dados
x1<- cbind(xc1,1)
x2<- cbind(xc2,-1)
X <- rbind(x1[,1:2], x2[,1:2])
aux1<-x1[,3]
aux2<-x2[,3]
Y <- cbind(aux1,aux2)
Y <- matrix(Y, ncol =1, nrow = nc*4)

# Treinando
p<-5
Z<-replicate(p,runif(3,-0.5,0.5))
Xaug<-cbind(1,X)
H<-tanh(Xaug %*% Z)

W<-pseudoinverse(H) %*% Y

yhat_train<-sign(H %*% W)
e_train<-sum((Y-yhat_train)^2)/4


#plotando o contorno


seqi<-seq(0,6,0.1)
seqj<-seq(0,6,0.1)

M<- matrix(0,nrow=length(seqi),ncol=length(seqj))
ci<-0
for (i in seqi){
  ci<-ci+1
  cj<-0
  for(j in seqj){
    cj<-cj+1
    xin<-c(1,i,j)
    xin<-tanh(xin %*% Z)
    M[ci,cj]<-(sign(xin %*% W))
  }
}
plot(xc1[,1],xc1[,2],col='red', xlim = c(0,6), ylim = c(0,6), xlab = 'x_1', ylab = 'x_2')
par(new=T)
plot(xc2[,1],xc2[,2],col = 'blue', xlim= c(0,6), ylim=c(0,6), xlab='', ylab = '')
par(new=T)
contour(seqi,seqj,M,xlim=c(0,6),ylim=c(0,6),xlab='',ylab='')
print(e_train)