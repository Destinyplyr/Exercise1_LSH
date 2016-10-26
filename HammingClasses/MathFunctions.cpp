double dot_product(double* vector1, double* vector2, int vector_size) {
	double dot_product = 0;
	for (int i =0; i < vector_size; i++) {
		dot_product += vector1[i] * vector2[i];
	}
	return dot_product;
}