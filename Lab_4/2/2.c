#include <stdio.h>
#include <stdlib.h>

long comparisons = 0; // global counter

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high, int *scenarioFlag) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    int pos = i + 1;
    int leftSize = pos - low;
    int rightSize = high - pos;

    // Determine partition scenario (best/worst)
    if (leftSize == 0 || rightSize == 0)
        *scenarioFlag = 2; // worst-case
    else if (abs(leftSize - rightSize) <= 1)
        *scenarioFlag = 1; // best-case

    return pos;
}

void quickSort(int arr[], int low, int high, int *scenarioFlag) {
    if (low < high) {
        int pi = partition(arr, low, high, scenarioFlag);
        quickSort(arr, low, pi - 1, scenarioFlag);
        quickSort(arr, pi + 1, high, scenarioFlag);
    }
}

int readFile(const char *filename, int arr[]) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Error opening %s\n", filename);
        return 0;
    }
    int n = 0;
    while (fscanf(f, "%d", &arr[n]) != EOF) {
        n++;
    }
    fclose(f);
    return n;
}

void writeFile(const char *filename, int arr[], int n) {
    FILE *f = fopen(filename, "w");
    for (int i = 0; i < n; i++)
        fprintf(f, "%d ", arr[i]);
    fclose(f);
}

int main() {
    int choice;
    int arr[600], n;
    char inFile[20], outFile[20];

    printf("MAIN MENU (QUICK SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. ERROR (EXIT)\n");
    printf("Enter option: ");
    scanf("%d", &choice);

    if (choice == 1) {
        sprintf(inFile, "inAsce.dat");
        sprintf(outFile, "outQuickAsce.dat");
    } else if (choice == 2) {
        sprintf(inFile, "inDesc.dat");
        sprintf(outFile, "outQuickDesc.dat");
    } else if (choice == 3) {
        sprintf(inFile, "inRand.dat");
        sprintf(outFile, "outQuickRand.dat");
    } else {
        printf("Exit.\n");
        return 0;
    }

    // Read input
    n = readFile(inFile, arr);

    printf("Before Sorting (from %s):\n", inFile);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    comparisons = 0;
    int scenarioFlag = 0; // 0=neutral, 1=best, 2=worst
    quickSort(arr, 0, n - 1, &scenarioFlag);

    // Write output
    writeFile(outFile, arr, n);

    printf("After Sorting (stored in %s):\n", outFile);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Number of Comparisons: %ld\n", comparisons);

    if (scenarioFlag == 1)
        printf("Scenario: Best-case\n");
    else if (scenarioFlag == 2)
        printf("Scenario: Worst-case\n");
    else
        printf("Scenario: Average-case\n");

    return 0;
}
