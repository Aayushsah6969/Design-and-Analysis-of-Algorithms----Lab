#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    // Base case: if b is 0, then GCD is a
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main(int argc, char* argv[]) {
    
    char* input_file = argv[1];
    char* output_file = argv[2];
    
    FILE *f_in, *f_out;
    int num1, num2, result;
    
    f_in = fopen(input_file, "r");
    f_out = fopen(output_file, "w");
    
    while (fscanf(f_in, "%d %d", &num1, &num2) == 2) {
        result = gcd(num1, num2);
        fprintf(f_out, "The GCD of %d and %d is %d\n", num1, num2, result);
    }
    
    fclose(f_in);
    fclose(f_out);
    
    printf("GCD results stored in %s:\n", output_file);
    
    f_out = fopen(output_file, "r"); 
    char line[200];
    while (fgets(line, sizeof(line), f_out)) {
        printf("%s", line);
    }
    
    fclose(f_out);
    
    return 0;
}
