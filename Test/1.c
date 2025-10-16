#include <stdio.h>
#include <limits.h>

#define N 6  // number of matrices

int main() {
    // Example: matrices A1..A6 with dimensions {30,35,15,5,10,20,25}
    int p[] = {30, 35, 15, 5, 10, 20, 25};
    int n = N;   // number of matrices = length(p) - 1

    int m[N+1][N+1];  // DP table to store minimum cost

    // cost is zero when multiplying one matrix
    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    // L = chain length
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    printf("Minimum number of multiplications: %d\n", m[1][n]);
    return 0;
}

