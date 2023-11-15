rm(list = ls())
require(RnavGraphImageData)

# Carregando a Base de dados
data( faces )
faces <- t( faces )
MostraImagem <- function( x, k, titulo )
{
  rotate <- function(x) t( apply(x, 2, rev) )
  imagem <- matrix( x, nrow=k )
  cor <- rev( gray(50:1/50) )
  image( rotate( imagem ), col=cor, main=titulo)
  return(imagem)
}

tituloImagemOriginal <- "Imagem original"
numeroImgOriginal <- 100
img = MostraImagem(faces[numeroImgOriginal,], 64, tituloImagemOriginal)

dimx = dim(img)[1]
dimy = dim(img)[2]

tf = 3

# Filtro de bordas
f = matrix(c(-1,-1,-1,-1,8,-1,-1,-1,-1), nrow = tf, ncol = tf)
M = matrix(0, nrow=(dimx-2), ncol=(dimy-2))

for (l in 1: (dimx-tf)){
  for (c in 1: (dimy-tf)){
    M[l,c]=sum(img[l:(l+2), c:(c+2)] * f)
  }
}

MostraImagem(M, 62, "Imagem com filtro de bordas")

# Filtro de linhas verticais
f = matrix(c(1,2,1,0,0,0,-1,-2,-1), nrow = tf, ncol = tf)
M = matrix(0, nrow=(dimx-2), ncol=(dimy-2))

for (l in 1: (dimx-tf)){
  for (c in 1: (dimy-tf)){
    M[l,c]=sum(img[l:(l+2), c:(c+2)] * f)
  }
}
MostraImagem(faces[numeroImgOriginal,], 64, tituloImagemOriginal)
MostraImagem(M, 62, "Imagem com filtro de linhas verticais")

# Filtro de linhas horizontais
f = matrix(c(1,0,-1,2,0,-2,1,0,-1), nrow = tf, ncol = tf)
M = matrix(0, nrow=(dimx-2), ncol=(dimy-2))

for (l in 1: (dimx-tf)){
  for (c in 1: (dimy-tf)){
    M[l,c]=sum(img[l:(l+2), c:(c+2)] * f)
  }
}
MostraImagem(faces[numeroImgOriginal, ], 64, tituloImagemOriginal)
MostraImagem(M, 62, "Imagem com filtro de linhas horizontais")

# Filtro Sharpen
f = matrix(c(0,-1,0,-1,5,-1,0,-1,0), nrow = tf, ncol = tf)
M = matrix(0, nrow=(dimx-2), ncol=(dimy-2))

for (l in 1: (dimx-tf)){
  for (c in 1: (dimy-tf)){
    M[l,c]=sum(img[l:(l+2), c:(c+2)] * f)
  }
}
MostraImagem(faces[numeroImgOriginal,], 64, tituloImagemOriginal)
MostraImagem(M, 62, "Imagem com filtro Sharpen") 
