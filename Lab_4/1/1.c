#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500

long long comparisons = 0;

// Merge function with comparison count
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

// Merge sort recursive
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Read from file
int readFromFile(const char *filename, int arr[]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }

    int count = 0;
    while (fscanf(fp, "%d", &arr[count]) == 1 && count < MAX) {
        count++;
    }

    fclose(fp);
    return count;
}

// Write to file
void writeToFile(const char *filename, int arr[], int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", arr[i]);
    }
    fclose(fp);
}

int main() {
    int option;
    int arr[MAX], n;
    char inFile[50], outFile[50];

    printf("MAIN MENU (MERGE SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");
    printf("Enter option: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            sprintf(inFile, "inAsce.dat");
            sprintf(outFile, "outMergeAsce.dat");
            break;
        case 2:
            sprintf(inFile, "inDesc.dat");
            sprintf(outFile, "outMergeDesc.dat");
            break;
        case 3:
            sprintf(inFile, "inRand.dat");
            sprintf(outFile, "outMergeRand.dat");
            break;
        default:
            printf("Exiting...\n");
            return 0;
    }

    // Read data
    n = readFromFile(inFile, arr);

    // Show before sorting
    printf("Before Sorting: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // Measure execution time
    clock_t start = clock();
    mergeSort(arr, 0, n - 1);
    clock_t end = clock();

    // Show after sorting
    printf("After Sorting: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // Write to output file
    writeToFile(outFile, arr, n);

    // Print stats
    double time_taken_ns = ((double)(end - start) / CLOCKS_PER_SEC) * 1e9;
    printf("Number of Comparisons: %lld\n", comparisons);
    printf("Execution Time: %.0f nanoseconds\n", time_taken_ns);

    return 0;
}
