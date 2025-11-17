#include <stdio.h>

// Function to swap two numbers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function with arr[low] as pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[low];  
    int i = low + 1;
    int j = high;

    while (1) {
        // Find element greater than pivot
        while (i <= high && arr[i] <= pivot) {
            i++;
        }

        // Find element smaller than pivot
        while (j >= low && arr[j] > pivot) {
            j--;
        }

        // If two pointers cross, break
        if (i >= j) {
            break;
        }

        // Swap elements at i and j
        swap(&arr[i], &arr[j]);
    }

    // Place pivot at correct position
    swap(&arr[low], &arr[j]);
    return j;  // New pivot index
}

// QuickSort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // partition index
        quickSort(arr, low, pi - 1);  // sort left part
        quickSort(arr, pi + 1, high); // sort right part
    }
}

int main() {
    int n = 7;
    int arr[] = {11, 24, 39, 46, 23, 17, 8};

    quickSort(arr, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
