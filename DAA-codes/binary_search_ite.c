#include <stdio.h>

int binarySearchIter(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;              // found
        else if (arr[mid] < key)
            low = mid + 1;           // search right half
        else
            high = mid - 1;          // search left half
    }
    return -1;   // not found
}


int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 7;

    int result = binarySearchIter(arr, n, key);

    if (result != -1)
        printf("Found at index %d\n", result);
    else
        printf("Not found\n");

    return 0;
}
