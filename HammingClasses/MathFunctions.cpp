#include "MathFunctions.h"

double dot_product(double* vector1, double* vector2, int vector_size) {
	double dot_product = 0;
	for (int i =0; i < vector_size; i++) {
		dot_product += vector1[i] * vector2[i];
	}
	return dot_product;
}

double euclid_norm(double* vector1, int vector_size) {
    double norm = 0;
    for (int i = 0; i < vector_size; i++) {
        norm += (pow(vector1[i], 2));
    }
    return sqrt(norm);
}
