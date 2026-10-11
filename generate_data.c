#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int sizes[] = {25000, 50000, 100000, 125000};
    char filename[64];

    srand((unsigned)time(NULL));

    for (int s = 0; s < 4; s++) {
        int n = sizes[s];
        sprintf(filename, "data_%d.txt", n);

        FILE *fp = fopen(filename, "w");
        if (!fp) {
            printf("Error: Cannot create %s\n", filename);
            continue;
        }

        // Generate random numbers (1 to 1,000,000)
        for (int i = 0; i < n; i++) {
            int num = (rand() % 1000000) + 1;
            fprintf(fp, "%d\n", num);
        }

        fclose(fp);
        printf("Created %s with %d numbers\n", filename, n);
    }

    printf("\nAll data files generated successfully!\n");
    return 0;
}