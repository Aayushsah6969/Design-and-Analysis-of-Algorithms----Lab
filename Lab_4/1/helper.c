#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 300
#define MAX_SIZE 500

// Function to create ascending data
void createAscendingFile(const char *filename, int size) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }
    for (int i = 1; i <= size; i++) {
        fprintf(fp, "%d ", i * 10); // multiples of 10
    }
    fclose(fp);
    printf("%s created with ascending data.\n", filename);
}

// Function to create descending data
void createDescendingFile(const char *filename, int size) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }
    for (int i = size; i >= 1; i--) {
        fprintf(fp, "%d ", i * 10); // multiples of 10
    }
    fclose(fp);
    printf("%s created with descending data.\n", filename);
}

// Function to create random data
void createRandomFile(const char *filename, int size) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%d ", rand() % 1000); // random numbers between 0–999
    }
    fclose(fp);
    printf("%s created with random data.\n", filename);
}

int main() {
    srand(time(NULL));

    // Random size between MIN_SIZE and MAX_SIZE
    int size = MIN_SIZE + rand() % (MAX_SIZE - MIN_SIZE + 1);
    printf("Creating files with %d elements each...\n", size);

    createAscendingFile("inAsce.dat", size);
    createDescendingFile("inDesc.dat", size);
    createRandomFile("inRand.dat", size);

    printf("All input files created successfully.\n");
    return 0;
}
