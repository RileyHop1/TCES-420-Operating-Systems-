#include "single.h"

double matrix_mult_single(
    int size,
    int (*matrix_a)[size],
    int (*matrix_b)[size],    
    int (*product_matrix)[size]

) {

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    //This is the naive algorithm simple to get setup.
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int sum = 0;
            for (int k = 0; k < size; ++k) {
                sum += matrix_a[i][k] * matrix_b[k][j];
            }
            product_matrix[i][j] = sum;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    return ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);
}
