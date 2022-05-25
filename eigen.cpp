#include <algorithm>
#include <chrono>
#include <iostream>
#include "eigen.h"

using namespace std;


pair<double, Vector> power_iteration(const Matrix& X, unsigned num_iter, double eps){
    Vector b = Vector::Random(X.cols());
    
    double eigenvalue;

    b = b / b.norm();

    for(unsigned int i = 0; i < num_iter; i++){
        Vector old = b;
        b = X * b;
        b = b / b.norm();

        double cos_angle = b.dot(old);

        if( (1-eps) < cos_angle && cos_angle <= 1)
            break;
    }

    eigenvalue = b.dot((X * b));

    return make_pair(eigenvalue, b / b.norm());
}

pair<Vector, Matrix> get_first_eigenvalues(const Matrix& X, unsigned num, unsigned num_iter, double epsilon){
    Matrix A(X);
    Vector eigvalues(num);
    Matrix eigvectors(A.rows(), num);

    for(unsigned int i = 0; i < num; i++){
        pair<double, Vector> aux = power_iteration(A, num_iter, epsilon);
        double l = aux.first;
        Vector v = aux.second;

        eigvalues[i] = l;
        eigvectors.col(i) = v;

        A = A - l* (v * v.transpose());
        
    }


    return make_pair(eigvalues, eigvectors);
}
