
#include  "single.h"

int main(void) {
    const int size = 2000;
    srand(42);

    int (*a)[size] = create_matrix(size, 1);
    int (*b)[size] = create_matrix(size, 1);
    int (*c)[size] = create_matrix(size, 0);

    if (!a || !b || !c) {
        free(a); free(b); free(c);
        return EXIT_FAILURE;
    }

    double elapsed = matrix_mult_single(size, a, b, c);
    printf("Execution Time: %.9f seconds\n", elapsed);

    free(a);
    free(b);
    free(c);

    return EXIT_SUCCESS;
}
