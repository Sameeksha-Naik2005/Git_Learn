#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0) return 0;
        return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;

    int n = atoi(argv[1]), count = 0;
    int *a = malloc(n * sizeof(int));
    double t = omp_get_wtime();

    for (int i = 2; i <= n; i++)
        if (prime(i)) a[count++] = i;

        printf("Serial: %f s\n", omp_get_wtime()-t);

    int total = 0;
    t = omp_get_wtime();

    #pragma omp parallel for reduction(+:total)
    for (int i = 2; i <= n; i++)
        total += prime(i);

    printf("Parallel: %f s\n", omp_get_wtime()-t);
    printf("Primes: %d\nFirst 10: ", count);

    for (int i = 0; i < count && i < 10; i++)
        printf("%d ", a[i]);

    free(a);
}

