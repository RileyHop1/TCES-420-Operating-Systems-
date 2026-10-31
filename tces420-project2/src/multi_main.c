
#include "multi.h"

int main(int argc, char *argv[]) {
    if (argc != 2 || atoi(argv[1]) <= 0) {
        fprintf(stderr, "Usage: %s <thread_count>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int thread_count = atoi(argv[1]);
    const int size = 2000;
    srand(42);

    int (*a)[size] = create_matrix(size, 1);
    int (*b)[size] = create_matrix(size, 1);
    int (*c)[size] = create_matrix(size, 0);

    if (!a || !b || !c) {
        free(a); free(b); free(c);
        return EXIT_FAILURE;
    }

    double elapsed = matrix_mult_multi(thread_count, size, a, b, c);
    if (elapsed < 0) {
        free(a); free(b); free(c);
        return EXIT_FAILURE;
    }

    printf("Execution Time: %.9f seconds\n", elapsed);

    free(a);
    free(b);
    free(c);

    return EXIT_SUCCESS;
}
