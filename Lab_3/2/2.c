#include<stdio.h>

void insertionSort(int arr[], int N){
    for (int i = 1; i < N; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

int main(int* argc, char *argv[]) {

    FILE *f_in, *f_out;
    char* input_file = argv[1];
    char* output_file = argv[2];

    f_in = fopen(input_file, "r");
    f_out = fopen(output_file, "w");

    int arr[100];
    int count =0;
    while(fscanf(f_in, "%d", &arr[count])==1){
        count++;
    }
    printf("Original Array: \n");
    for(int j=0; j<count; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");

    int size = sizeof(arr)/sizeof(arr[0]);
    insertionSort(arr, count);

    for(int k=0; k<count; k++) {
        printf("%d ",arr[k]);
        fprintf(f_out, "%d ", arr[k]);
    }
    printf("\n");


    fclose(f_in);
    fclose(f_out);
    return 0;
}