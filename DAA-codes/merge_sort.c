#include <stdio.h>


// Function to print array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) 
        printf("%d ", arr[i]);
    printf("\n");
}

// Function to merge two halves
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;

    int n1 = mid - left + 1;  // Size of left half
    int n2 = right - mid;     // Size of right half

    int L[n1], R[n2];
    
    for (i = 0; i < n1; i++) 
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++) 
        R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) 
            arr[k++] = L[i++];
        else 
            arr[k++] = R[j++];
    }

    // Copy remaining elements
    while (i < n1) 
        arr[k++] = L[i++];
    while (j < n2) 
        arr[k++] = R[j++];
}

// Recursive merge sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}



// Main function
int main() {
    int arr[] = {5, 4, 3, 6, 2, 5, 9, 8, 7, 3, 6, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n",size);

    printf("Original array:\n");
    printArray(arr, size);

    mergeSort(arr, 0, size - 1);

    printf("Sorted array:\n");
    printArray(arr, size);

    return 0;
}
