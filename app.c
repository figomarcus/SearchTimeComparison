#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


// Include headers of all trees
// #include "avl/avl.h"
// #include "trie/trie.h"
// #include "mway/mway.h"
// ... etc

#define MAX_SIZE 125000

int data[MAX_SIZE];
int n;

void loadData(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Cannot open %s\n", filename);
        exit(1);
    }
    n = 0;
    while (fscanf(fp, "%d", &data[n]) == 1 && n < MAX_SIZE)
        n++;
    fclose(fp);
    printf("Loaded %d keys from %s\n", n, filename);
}

double getTime() {
    return (double)clock() / CLOCKS_PER_SEC;
}

int main() {
    int sizes[] = {25000, 50000, 100000, 125000};
    char filename[50];

    printf("===== SEARCH TIME COMPARISON =====\n\n");

    for (int s = 0; s < 4; s++) {
        sprintf(filename, "data/data_%d.txt", sizes[s]);
        loadData(filename);

        // ---------- AVL Example ----------
        // AVL tree = create();
        // double start = getTime();
        // for(int i=0; i<n; i++) insert(&tree, data[i]);
        // double insertTime = getTime() - start;

        // start = getTime();
        // for(int i=0; i<n; i++) search(tree, data[i]);  // or random keys
        // double searchTime = getTime() - start;

        // destroy(&tree);

        // Print results for each tree...
        printf("Size: %d\n", sizes[s]);
        printf("AVL   → Insert: ?  Search: ?\n");
        printf("Trie  → Insert: ?  Search: ?\n");
        printf("m-Way → Insert: ?  Search: ?\n");
        printf("BST   → ...\n");
        printf("B+    → ...\n");
        printf("--------------------------------\n");
    }
    return 0;
}