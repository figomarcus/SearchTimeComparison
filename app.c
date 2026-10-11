#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Headers
#include "avl.h"
#include "bst.h"
#include "trie.h"
#include "mway.h"
#include "btree.h"
#include "bplustree.h"
#include "bstar.h"

#define MAX_SIZE 125000

int data[MAX_SIZE];
int n;

void loadData(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: Cannot open %s\n", filename);
        exit(1);
    }
    n = 0;
    while (n < MAX_SIZE && fscanf(fp, "%d", &data[n]) == 1)
        n++;
    fclose(fp);
    printf("Loaded %d keys from %s\n", n, filename);
}

double getTime() {
    return (double)clock() / CLOCKS_PER_SEC;
}

void intToStr(int num, char *str) {
    sprintf(str, "%d", num);
}

int main() {
    int sizes[] = {25000, 50000, 100000, 125000};
    char filename[64];
    char keyStr[20];

    printf("=====================================================\n");
    printf("     SEARCH TIME COMPARISON OF DIFFERENT TREES\n");
    printf("=====================================================\n\n");

    for (int s = 0; s < 4; s++) {
        sprintf(filename, "data_%d.txt", sizes[s]);
        loadData(filename);

        printf("\n========== Testing with %d keys ==========\n\n", sizes[s]);

        // -------------------- AVL --------------------
        {
            AVL tree = avl_create();
            double start, insertTime, searchTime;

            start = getTime();
            for (int i = 0; i < n; i++)
                avl_insert(&tree, data[i]);
            insertTime = getTime() - start;

            start = getTime();
            for (int i = 0; i < n; i++)
                avl_search(tree, data[i]);   // you need to add this function
            searchTime = getTime() - start;

            printf("AVL Tree     → Insert: %.4f sec   Search: %.4f sec\n", insertTime, searchTime);
            avl_destroy(&tree);
        }

        // -------------------- BST --------------------
        {
            BST tree = bst_create();
            double start, insertTime, searchTime;

            start = getTime();
            for (int i = 0; i < n; i++)
                bst_insert(&tree, data[i]);
            insertTime = getTime() - start;

            start = getTime();
            for (int i = 0; i < n; i++)
                bst_search(tree, data[i]);
            searchTime = getTime() - start;

            printf("BST          → Insert: %.4f sec   Search: %.4f sec\n", insertTime, searchTime);
            bst_destroy(&tree);
        }

        // -------------------- Trie --------------------
        {
            Trie t = createTrie();
            double start, insertTime, searchTime;

            start = getTime();
            for (int i = 0; i < n; i++) {
                intToStr(data[i], keyStr);
                insertTrie(t, keyStr);
            }
            insertTime = getTime() - start;

            start = getTime();
            for (int i = 0; i < n; i++) {
                intToStr(data[i], keyStr);
                searchTrie(t, keyStr);
            }
            searchTime = getTime() - start;

            printf("Trie         → Insert: %.4f sec   Search: %.4f sec\n", insertTime, searchTime);
            destroyTrie(t);
        }

        // -------------------- m-Way --------------------
        {
            MWayTree tree = mway_create();
            double start, insertTime, searchTime;

            start = getTime();
            for (int i = 0; i < n; i++)
                mway_insert(&tree, data[i]);
            insertTime = getTime() - start;

            start = getTime();
            for (int i = 0; i < n; i++)
                mway_search(tree, data[i]);  // add this function
            searchTime = getTime() - start;

            printf("m-Way Tree   → Insert: %.4f sec   Search: %.4f sec\n", insertTime, searchTime);
            mway_destroy(&tree);
        }

        // -------------------- B-Tree --------------------
        {
            BTree tree = btree_create();
            double start, insertTime, searchTime;

            start = getTime();
            for (int i = 0; i < n; i++)
                btree_insert(&tree, data[i]);
            insertTime = getTime() - start;

            start = getTime();
            for (int i = 0; i < n; i++)
                btree_search(tree, data[i]);
            searchTime = getTime() - start;

            printf("B-Tree       → Insert: %.4f sec   Search: %.4f sec\n", insertTime, searchTime);
            btree_destroy(&tree);
        }

        // -------------------- B+ Tree --------------------
        {
            BPlusTree tree = bplus_create();
            double start, insertTime, searchTime;

            start = getTime();
            for (int i = 0; i < n; i++)
                bplus_insert(&tree, data[i]);
            insertTime = getTime() - start;

            start = getTime();
            for (int i = 0; i < n; i++)
                bplus_search(tree, data[i]);
            searchTime = getTime() - start;

            printf("B+ Tree      → Insert: %.4f sec   Search: %.4f sec\n", insertTime, searchTime);
            bplus_destroy(&tree);
        }

        // -------------------- B* Tree --------------------
        {
            BStarTree tree = bstar_create();
            double start, insertTime, searchTime;

            start = getTime();
            for (int i = 0; i < n; i++)
                bstar_insert(&tree, data[i]);
            insertTime = getTime() - start;

            start = getTime();
            for (int i = 0; i < n; i++)
                bstar_search(tree, data[i]);
            searchTime = getTime() - start;

            printf("B* Tree      → Insert: %.4f sec   Search: %.4f sec\n", insertTime, searchTime);
            bstar_destroy(&tree);
        }

        printf("-----------------------------------------------------\n");
    }

    printf("\nAll tests completed!\n");
    return 0;
}