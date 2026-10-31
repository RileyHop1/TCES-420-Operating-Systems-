#include "multi.h"



double matrix_mult_multi(
    int thread_count,
    int size,
    int (*matrix_a)[size],
    int (*matrix_b)[size],    
    int (*product_matrix)[size]
) {
    if (thread_count < 1) {
        fprintf(stderr, "Error: Thread count and matrix size must be positive.\n");
        return -1.0;
    }

    struct timespec start, end;

    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));


    ThreadArgs *args = malloc(thread_count * sizeof(ThreadArgs)); 

     if (!threads || !args) {
        fprintf(stderr, "Error: Failed to allocate thread management memory.\n");

        free(threads);
        free(args);
        return -1.0;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < thread_count; ++i) {
        args[i].start = i;
        args[i].inc = thread_count;
        args[i].size = size;
        args[i].matrix_a = matrix_a;
        args[i].matrix_b = matrix_b;    
        args[i].product_matrix = product_matrix;

        int rc = pthread_create(
            &threads[i],
            NULL,
            matrix_mult_helper,
            &args[i]
        );

        if (rc != 0) {
            fprintf(stderr, "Error: Failed to create thread %d: %s\n",
                i, strerror(rc));
            return -1.0;
        }
    }

    for (int i = 0; i < thread_count; ++i) {

        int rc = pthread_join(threads[i], NULL);

        if (rc != 0) {
            fprintf(stderr, "Error: Failed to join thread %d: %s\n",
                    i, strerror(rc));
            return -1.0;
        }
    }


    
    clock_gettime(CLOCK_MONOTONIC, &end);

    free(threads);
    free(args);

    return ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9);
}


void *matrix_mult_helper(void *arg) {
    ThreadArgs *args = arg;

    int (*matrix_a)[args->size] = args->matrix_a;
    int (*matrix_b)[args->size] = args->matrix_b;
    int (*product_matrix)[args->size] = args->product_matrix;

   //This is the naive algorithm simple to get setup.
    for (int i = args->start; i < args->size; i+=args->inc) {
        for (int j = 0; j < args->size; ++j) {
            int sum = 0;
            for (int k = 0; k < args->size; ++k) {
                sum += matrix_a[i][k] * matrix_b[k][j];
            }
            product_matrix[i][j] = sum;
        }
    } 

    return NULL;
}