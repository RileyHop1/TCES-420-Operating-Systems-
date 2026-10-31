#ifndef MULTI_TYPE_BEAT
#define MULTI_TYPE_BEAT

#include <pthread.h>
#include <string.h>
#include "matrix.h"

typedef struct {
    int start;
    int inc;
    int size;

    void *matrix_a;
    void *matrix_b;
    void *product_matrix;
} ThreadArgs;

double matrix_mult_multi(
    int thread_count,
    int size,
    int (*matrix_a)[size],
    int (*matrix_b)[size],    
    int (*product_matrix)[size]
);

void *matrix_mult_helper(void *arg);






#endif
