#include <algorithm>
#include <numeric>
#include <iostream>
#include "knn.h"

using namespace std;


KNNClassifier::KNNClassifier(unsigned int n_neighbours){
    neighbours = n_neighbours;
}

void KNNClassifier::fit(Matrix X, Vector Y){
    sample = X;
    labels = Y;
}


Vector KNNClassifier::predict(Matrix X){

// Creamos vector columna a devolver
    auto ret = Vector(X.rows());

    for (unsigned k = 0; k < X.rows(); k++)
    {
        ret(k) = 0;
    }

//Vamos a recorrer cada imagen de la matriz y la clasificamos

   // cout << "Sample is " << sample << "\n";
   // cout << "X is " << X << "\n";
    for(unsigned i = 0; i < X.rows(); i++){

    //Armamos un vector que tiene la distancia entre la imagen i-ésima que estemos intentando clasificar
    //y las imagenes que tenemos en nuestra base de datos.

        Vector Norms(sample.rows());

        for(unsigned j = 0; j < sample.rows(); j++){
           // cout << "Sample row "<< j << " "  << sample.row(j) << "\n";
            //cout << "X row "<< j << " " <<X.row(i) << "\n";
            Norms[j] = (sample.row(j)-X.row(i)).squaredNorm();
            //cout << "Norm es " << Norms[j] << "\n";
        }
        
    //Ahora, armamos un vector que tiene los ìndices de las imagenes en la base de datos y ordenamos estos indices
    //Comparando las distancias a la imagen a clasificar de cada una de las imagenes asociadas a los indices.
    //De ese vector solo nos quedamos con una cantidad de elementos igual a la cantidad de vecinos que queremos.

        Vector idx(Norms.size());
        for (int id = 0; id < idx.size(); id++) {
            idx[id] = id;
        }

        sort(idx.data(), idx.data() + idx.size(), [&Norms](size_t a, size_t b){return Norms(a) < Norms(b);});

        //for (int s = 0; s < idx.size(); s++) {
            //cout << "Las normas ordenadas son " << idx[s] << "\n";
        //}
        //idx.resize(neighbours);

        //for (int s = 0; s< idx.size(); s++) {
          //  cout << "Id es " << idx[s] << "\n";
        //}    
    //Ahora queremos, para las imagenes cuyos indices quedaron en el vector idx, que etiquetas tienen
    //y guardar las mismas en un vector
        Vector labelsOfIdx(neighbours);
        for(unsigned m = 0; m < neighbours; m++){
            labelsOfIdx(m) = labels(idx(m));
        }

        //for (int s =0 ; s < labelsOfIdx.size();s++) {
         //   cout << "LabelOfIndex es " << labelsOfIdx[s] << "\n";
       // }

    //Ahora vamos a medir la ocurrencia de cada una de las etiquetas fijandonos cuantas veces aparece cada una
        
        
        int size = 10;
        Vector labelOcurrencies(size);

        for(unsigned n = 0; n < labelOcurrencies.size(); n++){
            labelOcurrencies(n) = 0;
        }

        for(unsigned n = 0; n < labelsOfIdx.size(); n++){
            labelOcurrencies(labelsOfIdx(n))++;
        }

        //for (int s =0 ; s < labelOcurrencies.size();s++) {
         //   cout << "labelOcurrencies es " << labelOcurrencies[s] << "\n";
        //}

    //Vemos cual es la predicción para la imagen i-ésima viendo como quedo la modad de las etiquetas en el vector.
        int prediction = 0;
        for(unsigned k = 0; k < labelOcurrencies.size(); k++){
            if(labelOcurrencies(k) > prediction){
                prediction = k;
            }
        }

    //cout << "prediction es " << prediction << "\n";
    //Guardamos las etiquetas en el vector a devolver
        ret(i) = prediction;
    
    }
    
    return ret;
}

