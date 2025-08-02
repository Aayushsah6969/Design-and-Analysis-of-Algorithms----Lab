#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Comparator for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// O(n) approach using hash table
void findPairsHash(int *arr, int n, int target, FILE *out) {
    fprintf(out, "Pairs with sum %d using O(n) approach:\n", target);
    int hash[10000] = {0}; // Assumes numbers are within reasonable bounds
    for (int i = 0; i < n; i++) {
        int complement = target - arr[i];
        if (hash[complement]) {
            fprintf(out, "(%d, %d), ", complement, arr[i]);
        }
        hash[arr[i]] = 1;
    }
    fprintf(out, "\n");
}

// O(n log n) approach using sorting and two pointers
void findPairsTwoPointer(int *arr, int n, int target, FILE *out) {
    fprintf(out, "Pairs with sum %d using O(n log n) approach:\n", target);
    qsort(arr, n, sizeof(int), compare);
    int left = 0, right = n - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) {
            fprintf(out, "(%d, %d), ", arr[left], arr[right]);
            left++;
            right--;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    fprintf(out, "\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (!src) {
        perror("Error opening source file");
        return 1;
    }

    FILE *dest = fopen(argv[2], "w");
    if (!dest) {
        perror("Error opening destination file");
        fclose(src);
        return 1;
    }

    int target, value, capacity = 100, size = 0;
    int *arr = (int*)malloc(capacity * sizeof(int));

    if (fscanf(src, "%d", &target) != 1) {
        fprintf(stderr, "Invalid input format.\n");
        fclose(src);
        fclose(dest);
        free(arr);
        return 1;
    }

    while (fscanf(src, "%d", &value) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            arr = realloc(arr, capacity * sizeof(int));
        }
        arr[size++] = value;
    }

    findPairsHash(arr, size, target, dest);
    findPairsTwoPointer(arr, size, target, dest);

    fclose(src);
    fclose(dest);
    free(arr);

    return 0;
}
