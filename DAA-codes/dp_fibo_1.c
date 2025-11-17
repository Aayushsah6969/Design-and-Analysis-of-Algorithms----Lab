#include <stdio.h>

#define MAX 100   // maximum n we can calculate
int memo[MAX];    // array to store computed results

int fib_top_down(int n) {
    if (memo[n] != -1) {
        return memo[n];   // if already computed, return it
    }
    if (n <= 1) {
        memo[n] = n;      // base case
    } else {
        memo[n] = fib_top_down(n-1) + fib_top_down(n-2);  // recursive with memo
    }
    return memo[n];
}

int main() {
    int n = 5;

    // initialize memo array with -1 (meaning "not computed")
    for (int i = 0; i < MAX; i++) {
        memo[i] = -1;
    }

    printf("Fibonacci(%d) = %d\n", n, fib_top_down(n));
    return 0;
}
