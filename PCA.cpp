#include <iostream>
#include "pca.h"
#include "eigen.h"

using namespace std;  

//Primero mirar pca.h

PCA::PCA(unsigned int n_components)
{
  alpha = n_components;
}

void PCA::fit(Matrix X)
{
//Calculamos el vector con las medias de cada uno de los pixeles
  Vector u = X.colwise().mean();

//Modificamos el X
  for (int i = 0; i < X.rows(); i++)
  {
      X.row(i) = (X.row(i) - u)/sqrt(X.rows()- 1);
  }
//Calculamos la matriz de covarianza
  Matrix Mx = X.transpose()* X;

//Nos quedamos solo con los primeros alpha autovectores de Mx
  eigenVectors = get_first_eigenvalues(Mx, alpha).second;
}


MatrixXd PCA::transform(Matrix X)
{
  //Aplicamos la transformación(diapo 22 de la presentación)
  return X*eigenVectors;
}
