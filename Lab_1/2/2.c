// Input Array:  3 4 5 1 2
// Output Array: 3 7 12 13 15

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
    int j=0;
    out[j]=arr[0];

    for (j = 1; j < i; j++)
    {
        out[j] =out[j-1] + arr[j];
    }
    int k;
    for (k = 0; k < i; k++)
    {
        printf("%d ", out[k]);
    }
    printf("\n");
    f_out = fopen("output.txt", "w");
    int l;
    for(l=0; l<i; l++){
        fprintf(f_out, "%d ", out[l]);
    }
    return 0;
}