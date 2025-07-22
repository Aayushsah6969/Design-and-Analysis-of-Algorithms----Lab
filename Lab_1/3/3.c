#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *f_in, *f_out;
    int arr[100];
    int out[100];
    int num, i = 0;

    f_in = fopen("input.txt", "r");
    if (f_in == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    while (fscanf(f_in, "%d", &num) == 1)
    {
        arr[i] = num;
        i++;
    }
    fclose(f_in);

    int j;
    printf("The content of the array: ");
    for(j=0; j<i; j++){
        printf("%d ",arr[j]);
    }
    printf("\n");

    int k, l, m;
   // ...existing code...

    // Count duplicates and find the most repeating element
    int duplicate_count = 0;
    int max_count = 0;
    int most_repeating = arr[0];

    for (j = 0; j < i; j++) {
        int count = 1;
        if (arr[j] == -1) continue; // Skip already counted elements
        for (k = j + 1; k < i; k++) {
            if (arr[j] == arr[k]) {
                count++;
                arr[k] = -1; // Mark as counted
            }
        }
        if (count > 1) {
            duplicate_count++;
        }
        if (count > max_count) {
            max_count = count;
            most_repeating = arr[j];
        }
    }

    printf("Total number of duplicate values = %d\n", duplicate_count);
    printf("The most repeating element in the array = %d\n", most_repeating);

    // Save results to output.txt
    f_out = fopen("output.txt", "w");
    if (f_out == NULL) {
        printf("Error opening output file\n");
        return 1;
    }
    fprintf(f_out, "Total number of duplicate values = %d\n", duplicate_count);
    fprintf(f_out, "The most repeating element in the array = %d\n", most_repeating);
    fclose(f_out);

    return 0;



}