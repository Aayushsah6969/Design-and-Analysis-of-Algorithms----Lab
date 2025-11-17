#include <stdio.h>

void findMinMax(int arr[], int low, int high, int *min, int *max) {
    int mid, min1, max1, min2, max2;

    // If one element
    if (low == high) {
        *min = *max = arr[low];
        return;
    }

    // If two elements
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            *min = arr[low];
            *max = arr[high];
        } else {
            *min = arr[high];
            *max = arr[low];
        }
        return;
    }

    // More than two elements
    mid = (low + high) / 2;

    // Recursively find min and max in left half
    findMinMax(arr, low, mid, &min1, &max1);

    // Recursively find min and max in right half
    findMinMax(arr, mid + 1, high, &min2, &max2);

    // Combine results
    *min = (min1 < min2) ? min1 : min2;
    *max = (max1 > max2) ? max1 : max2;
}

int main() {
    int arr[] = {12, 3, 5, 7, 19, 1, 21, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int min, max;

    findMinMax(arr, 0, n - 1, &min, &max);

    printf("Minimum element: %d\n", min);
    printf("Maximum element: %d\n", max);

    return 0;
}
