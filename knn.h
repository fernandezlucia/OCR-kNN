#pragma once

#include "types.h"


class KNNClassifier {
public:
    KNNClassifier(unsigned int n_neighbours);

    void fit(Matrix X, Vector Y);

    Vector predict(Matrix X);
private:
    //Cantidad de vecinos a considerar
    unsigned int neighbours;
    //Base de datos
    Matrix sample;
    //Etiquetas de las imagenes en la base de datos
    Vector labels;
};
