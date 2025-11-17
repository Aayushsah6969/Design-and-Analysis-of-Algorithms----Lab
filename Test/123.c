//randomized quick sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
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
int randomPartition(int arr[], int low, int high) {
    int random = low + rand() % (high - low + 1);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high);
}
int randomizedQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = randomPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}
    randomizedQuickSort(arr, 0, n - 1);
// 
//     // Write sorted numbers to file
//     for (int i = 0; i < n; i++) {
//         fprintf(outfile, "%d\n", arr[i]);
//     }
// 
//     fclose(outfile);
//     return 0;
// }
    FILE *infile, *outfile;
    int arr[500], n = 0;

    infile = fopen("input.txt", "r");
    outfile = fopen("output.txt", "w");

    if (infile == NULL || outfile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fscanf(infile, "%d", &arr[n]) != EOF) {
        n++;
    }

    fclose(infile);

    randomizedQuickSort(arr, 0, n - 1);

    // Write sorted numbers to file
    for (int i = 0; i < n; i++) {
        fprintf(outfile, "%d\n", arr[i]);
    }

    fclose(outfile);
    return 0;