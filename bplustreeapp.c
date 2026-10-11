/*
    File: bplustreeapp.c
    Menu-driven program for B+ Tree
*/

#include <stdio.h>
#include <stdlib.h>
#include "bplustree.h"

int main() {
    BPlusTree tree = bplus_create();
    int choice, value;

    while (1) {
        printf("\n========== B+ Tree Menu ==========\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print (leaf sequence)\n");
        printf("4. Destroy Tree\n");
        printf("5. Run Test Cases\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                bplus_insert(&tree, value);
                printf("%d inserted.\n", value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                bplus_delete(&tree, value);
                break;

            case 3:
                bplus_print(tree);
                break;

            case 4:
                bplus_destroy(&tree);
                tree = bplus_create();
                printf("Tree destroyed.\n");
                break;

            case 5:
                bplus_runTests();
                break;

            case 6:
                bplus_destroy(&tree);
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}