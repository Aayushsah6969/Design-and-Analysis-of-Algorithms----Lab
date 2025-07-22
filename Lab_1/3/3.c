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
    for()


}