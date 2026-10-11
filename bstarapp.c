/*
    File: bstarapp.c
    Menu-driven program for B* Tree
*/

#include <stdio.h>
#include <stdlib.h>
#include "bstar.h"

int main() {
    BStarTree tree = bstar_create();
    int choice, value;

    while (1) {
        printf("\n========== B* Tree Menu ==========\n");
        printf("1. Insert\n");
        printf("2. Print\n");
        printf("3. Destroy Tree\n");
        printf("4. Run Test Cases\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                bstar_insert(&tree, value);
                printf("%d inserted.\n", value);
                break;

            case 2:
                printf("Keys: ");
                bstar_print(tree);
                printf("\n");
                break;

            case 3:
                bstar_destroy(&tree);
                tree = bstar_create();
                printf("Tree destroyed.\n");
                break;

            case 4:
                bstar_runTests();
                break;

            case 5:
                bstar_destroy(&tree);
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}