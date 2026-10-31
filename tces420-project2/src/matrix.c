#include "matrix.h"


void* create_matrix(int _size, char random) {

    //We don't need to calloc this matrix
    int (*matrix)[_size] = malloc((_size * _size ) * sizeof(int));
    int upper_bound = 50;
    int lower_bound = 0;


    //Some absolutely disgusting code for you to read
    if (random == 1)
        for (int i = 0; i < _size; ++i) 
            for (int j = 0; j < _size; ++j)
                matrix[i][j] = rand() % (upper_bound - lower_bound + 1) + lower_bound;


    return matrix; 
}