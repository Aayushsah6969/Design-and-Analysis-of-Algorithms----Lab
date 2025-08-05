#include <stdio.h>

int main(int* argc, char* argv[]) {

    char* input_file = argv[1];
    char* output_file = argv[2];
    FILE *f_in, *f_out;

    f_in = fopen(input_file, "r");
    if (f_in == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }
    f_out = fopen(output_file, "w");
    if (f_out == NULL) {
        printf("Error opening output file.\n");
        fclose(f_in);
        return 1;
    }

    int arr[100], count = 0;
    while (fscanf(f_in, "%d", &arr[count]) == 1) {
        count++;
    }
    printf("%d \n", count);
    printf("Original Array: \n");
    for(int j=0; j<count; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");

    //sorting here
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("Sorted Array: \n");
    for (int j = 0; j < count; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");

    // Write sorted array to output file
    for (int j = 0; j < count; j++) {
        fprintf(f_out, "%d ", arr[j]);
    }
    fprintf(f_out, "\n");


    fclose(f_in);
    fclose(f_out);
    return 0;
}