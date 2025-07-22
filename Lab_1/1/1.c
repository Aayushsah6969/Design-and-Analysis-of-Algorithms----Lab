#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr1, *fptr2;
    int arr[100];
    int i = 0;
    int num;
    int min, max;

    fptr1 = fopen("input.txt", "r");
    if (fptr1 == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    while (fscanf(fptr1, "%d", &num) == 1) {
        arr[i++] = num;
    }
    fclose(fptr1);

    if (i == 0) {
        printf("No numbers found in input file.\n");
        return 1;
    }

    min = arr[0] ;
    max = arr[0];
    for (int j = 1; j < i; j++) {
        if (arr[j] < min){
            min = arr[j];
        }

        if (arr[j] > max){
            max = arr[j];
        }
    }

    fptr2 = fopen("output.txt", "w");
    if (fptr2 == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }
    fprintf(fptr2, "Smallest in the data: %d\nLargest in the data: %d\n", min, max);
    fclose(fptr2);
    printf("Output Written Successfully\n");
    return 0;
}