#include <stdio.h>
#include <stdlib.h>

void EXCHANGE(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int *arr, int p2) {
    int i;
    for (i = p2 - 1; i > 0; i--) {
        EXCHANGE(&arr[i], &arr[i-1]);
    }
}

int main() {
    FILE *f_in, *f_out;
    int arr[100];
    int n = 0, num, i;
    int p2 = 5; // Number of elements to rotate

    f_in = fopen("input.txt", "r");
    if (f_in == NULL) {
        printf("Error opening input.txt\n");
        return 1;
    }
    while (fscanf(f_in, "%d", &num) == 1) {
        arr[n++] = num;
    }
    fclose(f_in);

    f_out = fopen("output.txt", "w");
    if (f_out == NULL) {
        printf("Error opening output.txt\n");
        return 1;
    }
    fprintf(f_out, "Before ROTATE: ");
    for (i = 0; i < n; i++) {
        fprintf(f_out, "%d ", arr[i]);
    }
    fprintf(f_out, "\n");

    ROTATE_RIGHT(arr, p2);

    fprintf(f_out, "After ROTATE: ");
    for (i = 0; i < n; i++) {
        fprintf(f_out, "%d ", arr[i]);
    }
    fprintf(f_out, "\n");
    fclose(f_out);

    return 0;
}
