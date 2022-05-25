#pragma once
#include "types.h"

class PCA {
public:
    PCA(unsigned int n_components);

    void fit(Matrix X);

    Eigen::MatrixXd transform(Matrix X);
private:
    //Cantidad de componenetes principales a considerar
    unsigned int alpha;
    //La matriz V de cambio de base que contiene todos los autovectoes de la matriz Mx
    Matrix eigenVectors;
};
