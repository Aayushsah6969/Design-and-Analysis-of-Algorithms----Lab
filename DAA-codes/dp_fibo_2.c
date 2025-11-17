#include <stdio.h>

int fib_bottom_up(int n) {
    if (n <= 1) {
        return n;   // base cases
    }

    int dp[n+1];    // array to store values
    dp[0] = 0;
    dp[1] = 1;

    // build table iteratively
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }

    return dp[n];   // final answer
}

int main() {
    int n = 5;
    printf("Fibonacci(%d) = %d\n", n, fib_bottom_up(n));
    return 0;
}
