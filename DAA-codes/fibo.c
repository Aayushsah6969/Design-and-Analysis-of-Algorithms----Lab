#include <stdio.h>

int fib_recursive(int n) {
    if (n <= 1) {
        return n;   // base case: fib(0)=0, fib(1)=1
    }
    return fib_recursive(n-1) + fib_recursive(n-2); // recursive relation
}

int main() {
    int n = 10;
    printf("Fibonacci(%d) = %d\n", n, fib_recursive(n));
    return 0;
}
