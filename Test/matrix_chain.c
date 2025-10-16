// matrix_chain.c
// Compile: gcc -O2 -std=c11 matrix_chain.c -o matrix_chain
// Run example: ./matrix_chain

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// print optimal parenthesization using s table
void print_optimal_parens(int **s, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        print_optimal_parens(s, i, s[i][j]);
        print_optimal_parens(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Compute matrix chain order
// p[] has length n+1 for n matrices: A1 is p[0] x p[1], ..., An is p[n-1] x p[n]
long long** allocate_longlong_matrix(int n) {
    long long **m = malloc((n+1) * sizeof(long long*));
    for (int i = 0; i <= n; ++i) m[i] = malloc((n+1) * sizeof(long long));
    return m;
}

int** allocate_int_matrix(int n) {
    int **m = malloc((n+1) * sizeof(int*));
    for (int i = 0; i <= n; ++i) m[i] = malloc((n+1) * sizeof(int));
    return m;
}

void free_longlong_matrix(long long **m, int n) {
    for (int i = 0; i <= n; ++i) free(m[i]);
    free(m);
}
void free_int_matrix(int **m, int n) {
    for (int i = 0; i <= n; ++i) free(m[i]);
    free(m);
}

void matrix_chain_order(int p[], int n /*number of matrices*/, long long **m, int **s) {
    // m and s are sized at least (n+1) x (n+1). We'll use 1-based indexing for matrices.
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            m[i][j] = (i == j) ? 0LL : LLONG_MAX/4;
            s[i][j] = 0;
        }
    }

    // chain length L = 2..n
    for (int L = 2; L <= n; ++L) {
        for (int i = 1; i <= n - L + 1; ++i) {
            int j = i + L - 1;
            m[i][j] = LLONG_MAX/4;
            for (int k = i; k <= j - 1; ++k) {
                long long q = m[i][k] + m[k+1][j] + (long long)p[i-1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

int main(void) {
    // Example: read n and p[] from user, or use the classic example
    int choice;
    printf("Matrix Chain Multiplication\n");
    printf("1) Use classic example (p = {30,35,15,5,10,20,25})\n");
    printf("2) Enter your own dimensions\n");
    printf("Choose 1 or 2: ");
    if (scanf("%d", &choice) != 1) return 0;

    int n;
    int *p;
    if (choice == 1) {
        // classic example: 6 matrices
        int tmp[] = {30,35,15,5,10,20,25};
        n = 6;
        p = malloc((n+1) * sizeof(int));
        for (int i = 0; i <= n; ++i) p[i] = tmp[i];
    } else {
        printf("Enter number of matrices (n >= 1): ");
        if (scanf("%d", &n) != 1 || n < 1) { printf("Invalid n\n"); return 0; }
        p = malloc((n+1) * sizeof(int));
        printf("Enter %d+1 = %d dimensions p0 p1 ... p%d (space separated):\n", n, n+1, n);
        for (int i = 0; i <= n; ++i) {
            if (scanf("%d", &p[i]) != 1) { printf("Invalid input\n"); free(p); return 0; }
        }
    }

    // allocate DP tables
    long long **m = allocate_longlong_matrix(n);
    int **s = allocate_int_matrix(n);

    matrix_chain_order(p, n, m, s);

    printf("\nMinimum number of scalar multiplications: %lld\n", m[1][n]);
    printf("Optimal parenthesization: ");
    print_optimal_parens(s, 1, n);
    printf("\n");

    // clean up
    free_longlong_matrix(m, n);
    free_int_matrix(s, n);
    free(p);
    return 0;
}
