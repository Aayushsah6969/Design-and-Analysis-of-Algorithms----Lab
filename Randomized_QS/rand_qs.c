#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// This function places the pivot in its correct position
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Randomized partition
int randomPartition(int arr[], int low, int high) {
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high);
}

// Randomized quicksort
void randomizedQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = randomPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

int main() {
    FILE *infile, *outfile;
    int arr[500], n = 0;

    infile = fopen("in.dat", "r");
    outfile = fopen("out.dat", "w");

    if (infile == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    // Read numbers from file
    while (fscanf(infile, "%d", &arr[n]) != EOF && n < 500)
        n++;
    fclose(infile);

    srand(time(NULL)); // initialize random seed

    // Sort the array
    randomizedQuickSort(arr, 0, n - 1);

    // Write sorted numbers to file
    for (int i = 0; i < n; i++)
        fprintf(outfile, "%d\n", arr[i]);

    fclose(outfile);
    printf("Sorting complete! Output saved to output.txt\n");
    return 0;
}
