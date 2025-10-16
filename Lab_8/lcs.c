#include <stdio.h>
#include <string.h>

// A utility function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}


void findLCS(char *X, char *Y, int m, int n) {
    // Create a 2D array to store lengths of LCSs
    int L[m + 1][n + 1];
    int i, j;

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0; // If one string is empty, LCS is 0
            else if (X[i - 1] == Y[j - 1])
                // If last characters match, length is 1 + LCS of the rest
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                // If last characters don't match, take max of the two subproblems
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    int index = L[m][n];
    printf("\nLCS Length: %d\n", index);


    char lcs[index + 1];
    lcs[index] = '\0'; // Set the terminating null character

    i = m;
    j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1]; // Put current character in result
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    printf("LCS: %s\n", lcs);
}


int main() {
    char s1[100], s2[100];

    printf("Enter the first string: ");
    scanf("%s", s1);

    printf("Enter the second string: ");
    scanf("%s", s2);

    int m = strlen(s1);
    int n = strlen(s2);

    findLCS(s1, s2, m, n);

    return 0;
}
