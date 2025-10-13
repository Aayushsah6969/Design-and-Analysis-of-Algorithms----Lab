#include <stdio.h>
#include <limits.h>

// Global variables for M and S tables
int m[10][10];
int s[10][10];
int p[10]; // To store dimensions
int n;     // Number of matrices

// Function to print the optimal parenthesization
void printOptimalParens(int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(i, s[i][j]);
        printOptimalParens(s[i][j] + 1, j);
        printf(")");
    }
}

// Function to perform matrix chain multiplication algorithm
void matrixChainOrder() {
    int i, j, k, l, q;

    // Cost is 0 when multiplying one matrix.
    for (i = 1; i <= n; i++)
        m[i][i] = 0;

    // l is the chain length.
    for (l = 2; l <= n; l++) {
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            m[i][j] = INT_MAX; // Initialize with a large value

            for (k = i; k <= j - 1; k++) {
                // q = cost/scalar multiplications
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

int main() {
    int i;
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    printf("Enter dimensions (p array):\n");
    for (i = 0; i <= n; i++) {
        printf("p[%d]: ", i);
        scanf("%d", &p[i]);
    }
    
    // Note: The provided PDF asks for row/col pairs.
    // For simplicity and standard algorithm implementation, this code
    // takes the consolidated 'p' array as input.
    // For Ai, dimensions are p[i-1] x p[i].
    // A simple validation would be to take row/col and ensure
    // col of A(i) == row of A(i+1), then build the p array.


    matrixChainOrder();

    printf("\nM Table:\n");
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
             if(col >= row)
                printf("%-8d", m[row][col]);
             else
                printf("%-8d", 0);
        }
        printf("\n");
    }

    printf("\nS Table:\n");
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            if(col > row)
               printf("%-8d", s[row][col]);
            else
               printf("%-8d", 0);
        }
        printf("\n");
    }

    printf("\nOptimal parenthesization: ");
    printOptimalParens(1, n);

    printf("\n\nThe optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n]);

    return 0;
}
