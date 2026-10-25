#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void merge(int a[], int l, int m, int r) {
    int *t = malloc((r-l+1) * sizeof(int));
    int i = l, j = m+1;
    int k = 0;

    while (i <= m && j <= r)
        t[k++] = a[i] <= a[j] ? a[i++] : a[j++];

    while (i <= m) t[k++] = a[i++];
    while (j <= r) t[k++] = a[j++];

    for (i = l; i <= r; i++) a[i] = t[i-l];
    free(t);
}

void sort(int a[], int l, int r, int depth) {
    if (l >= r) return;

    int m = (l+r)/2;

    if (depth > 0) {
        #pragma omp parallel sections
        {
            #pragma omp section
            sort(a, l, m, depth-1);

            #pragma omp section
            sort(a, m+1, r, depth-1);
        }
    } else {
        sort(a, l, m, 0);
        sort(a, m+1, r, 0);
    }

    merge(a, l, m, r);
}

int main() {
    int n = 1000000;
    int *a = malloc(n*sizeof(int)), *b = malloc(n*sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; i++) a[i] = b[i] = rand();

    double t = omp_get_wtime();
    sort(a, 0, n-1, 0);
    printf("Sequential: %f s\n", omp_get_wtime()-t);

    t = omp_get_wtime();
    sort(b, 0, n-1, 4);
    printf("Parallel: %f s\n", omp_get_wtime()-t);

    free(a);
    free(b);
}
