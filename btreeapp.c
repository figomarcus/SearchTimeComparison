/*
    File: btreeapp.c
    Menu driven program for B-Tree
*/

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int main() {
    BTree tree = btree_create();
    int choice, value;

    while (1) {
        printf("\n========== B-Tree Menu ==========\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print (sorted order)\n");
        printf("4. Destroy Tree\n");
        printf("5. Run Test Cases\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter integer value to insert: ");
                scanf("%d", &value);
                btree_insert(&tree, value);
                printf("%d inserted successfully.\n", value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                btree_delete(&tree, value);
                break;

            case 3:
                if (tree == NULL || tree->n == 0)
                    printf("Tree is empty.\n");
                else {
                    printf("Keys in sorted order: ");
                    btree_print(tree);
                    printf("\n");
                }
                break;

            case 4:
                btree_destroy(&tree);
                tree = btree_create();   // create fresh empty tree
                printf("Tree destroyed.\n");
                break;

            case 5:
                btree_runTests();
                break;

            case 6:
                btree_destroy(&tree);
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}