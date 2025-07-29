#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimalToBinary(int num, char* binary, int index) {
    if (num == 0) {
        return;
    }
    decimalToBinary(num / 2, binary, index - 1);
    binary[index] = (num % 2) + '0';
}

// 16 bit binary representation
void getBinary16Bit(int num, char* binary) {
    strcpy(binary, "0000000000000000");
    binary[16] = '\0';
    
    decimalToBinary(num, binary, 15);
}

int main(int argc, char* argv[]) {

    int n = atoi(argv[1]);
    char* input_file = argv[2];
    char* output_file = argv[3];
    
    FILE *f_in, *f_out;
    int num, count = 0;
    char binary[17];
    
    f_in = fopen(input_file, "r");
    f_out = fopen(output_file, "w");

    
    while (count < n && fscanf(f_in, "%d", &num) == 1) {
        getBinary16Bit(num, binary);
        fprintf(f_out, "The binary equivalent of %d is %s\n", num, binary);
        count++;
    }
    
    fclose(f_in);
    fclose(f_out);
    
    printf("Content of the first %d decimal and their equivalent binary numbers:\n", count);
    
    f_out = fopen(output_file, "r");

    
    char line[100];
    while (fgets(line, sizeof(line), f_out)) {
        printf("%s", line);
    }
    
    fclose(f_out);
    
    return 0;
}