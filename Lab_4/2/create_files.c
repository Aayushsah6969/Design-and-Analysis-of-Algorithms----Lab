#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fa, *fd, *fr;
    int n = 300; // can change to between 300–500

    fa = fopen("inAsce.dat", "w");
    fd = fopen("inDesc.dat", "w");
    fr = fopen("inRand.dat", "w");

    if (!fa || !fd || !fr) {
        printf("Error opening file!\n");
        return 1;
    }

    // Ascending numbers
    for (int i = 10; i < 10 + n*10; i += 10)
        fprintf(fa, "%d ", i);

    // Descending numbers
    for (int i = n*10; i >= 10; i -= 10)
        fprintf(fd, "%d ", i);

    // Random numbers
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        fprintf(fr, "%d ", rand() % 1000); // random 0–999

    fclose(fa);
    fclose(fd);
    fclose(fr);

    printf("Files created: inAsce.dat, inDesc.dat, inRand.dat\n");
    return 0;
}
