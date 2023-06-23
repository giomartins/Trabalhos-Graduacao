rm( list=ls() )
require(RnavGraphImageData)
require( caret )

# Carregando a Base de dados
data( faces )
faces <- t( faces )
MostraImagem <- function( x )
{
  rotate <- function(x) t( apply(x, 2, rev) )
  img <- matrix( x, nrow=sqrt(length(x)) )
  cor <- rev( gray(50:1/50) )
  image( rotate( img ), col=cor )
  return(img)
}
img = MostraImagem( faces[1,] )
dimx= dim(img)[1]
dimy = dim(img)[2]
tf = 3

#Bordas
f = matrix(c(-1,-1,-1,-1,8,-1,-1,-1,-1),nrow=tf, ncol = tf)
M = matrix(0,nrow=(dimx-2),ncol=(dimy-2))
for (l in 1: (dimx-tf+1)){
  for (c in 1: (dimy-tf+1)){
    M[l,c]=sum(img[l:(l+2) ,c:(c+2)] * f)
  }
}
MostraImagem( M )

#Bordas
f = matrix(c(-1,-1,-1,-1,-1,-1,-1,8,-1,-1,-1,-1,-1,-1,-1),nrow=5, ncol = tf)
M = matrix(0,nrow=(dimx-4),ncol=(dimy-2))
for (l in 1: (dimx-5)){
  for (c in 1: (dimy-tf)){
    M[l,c]=sum(img[l:(l+4) ,c:(c+2)] * f)
  }
}
MostraImagem( M )

#Sharpen
f = matrix(c(0,-1,0,-1,5,-1,0,-1,0),nrow=tf, ncol = tf)
M = matrix(0,nrow=(dimx-2),ncol=(dimy-2))
for (l in 1: (dimx-tf+1)){
  for (c in 1: (dimy-tf+1)){
    M[l,c]=sum(img[l:(l+2) ,c:(c+2)] * f)
  }
}
MostraImagem( M )

#Linhas Verticais
f = matrix(c(1,2,1,0,0,0,-1,-2,-1),nrow=tf, ncol = tf)
M = matrix(0,nrow=(dimx-2),ncol=(dimy-2))
for (l in 1: (dimx-tf+1)){
  for (c in 1: (dimy-tf+1)){
    M[l,c]=sum(img[l:(l+2) ,c:(c+2)] * f)
  }
}
MostraImagem( M )
MostraImagem( img )

#Olho
f = matrix(c(0,-1,0,-1,4,-1,0,-1,0),nrow=tf, ncol = tf)
M = matrix(0,nrow=(dimx-2),ncol=(dimy-2))
for (l in 1: (dimx-tf+1)){
  for (c in 1: (dimy-tf+1)){
    M[l,c]=sum(img[l:(l+2) ,c:(c+2)] * f)
  }
}
MostraImagem( M )

#Olho2
tf=5
f = matrix(c(0,0,-1,0,0,0,-1,-1,-1,0,-1,-1,4,-1,-1,0,-1,-1,-1,0,0,0,-1,0,0),nrow=tf, ncol = tf)
M = matrix(0,nrow=(dimx-4),ncol=(dimy-4))
for (l in 1: (dimx-tf+1)){
  for (c in 1: (dimy-tf+1)){
    M[l,c]=sum(img[l:(l+4) ,c:(c+4)] * f)
  }
}
MostraImagem( M )

