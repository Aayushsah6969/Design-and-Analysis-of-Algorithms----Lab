#include <stdio.h>

int binarySearchRec(int arr[], int low, int high, int key) {
    if (low > high)
        return -1;   // not found

    int mid = (low + high) / 2;

    if (arr[mid] == key)
        return mid;              // found
    else if (arr[mid] < key)
        return binarySearchRec(arr, mid + 1, high, key);  // right half
    else
        return binarySearchRec(arr, low, mid - 1, key);   // left half
}



int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 7;

    int result = binarySearchRec(arr, 0, n - 1, key);

    if (result != -1)
        printf("Found at index %d\n", result);
    else
        printf("Not found\n");

    return 0;
}
