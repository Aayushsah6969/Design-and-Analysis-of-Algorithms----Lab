#include <stdio.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftArr[n1], rightArr[n2];

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
      
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *f_in, *f_out;
    char* input_file = argv[1];
    char* output_file = argv[2];

    f_in = fopen(input_file, "r");
    if (f_in == NULL) {
        printf("Error: Cannot open input file %s\n", input_file);
        return 1;
    }
    
    f_out = fopen(output_file, "w");
    if (f_out == NULL) {
        printf("Error: Cannot create output file %s\n", output_file);
        fclose(f_in);
        return 1;
    }

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

    mergeSort(arr, 0, count-1);

    printf("Sorted Array: \n");
    for(int k=0; k<count; k++) {
        printf("%d ",arr[k]);
        fprintf(f_out, "%d ", arr[k]);
    }
    printf("\n");
    fprintf(f_out, "\n");

    fclose(f_in);
    fclose(f_out);
    return 0;
}