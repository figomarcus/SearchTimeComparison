/*
    File: bstapp.c
    Menu driven program for Binary Search Tree
*/

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main() {
    BST tree = bst_create();
    int choice, value;

    while (1) {
        printf("\n========== Binary Search Tree Menu ==========\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print (Inorder)\n");
        printf("4. Destroy Tree\n");
        printf("5. Run Test Cases\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter integer value to insert: ");
                scanf("%d", &value);
                bst_insert(&tree, value);
                printf("%d inserted successfully.\n", value);
                break;

            case 2:
                if (tree == NULL) {
                    printf("Tree is empty. Nothing to delete.\n");
                } else {
                    printf("Enter integer value to delete: ");
                    scanf("%d", &value);
                    bst_delete(&tree, value);
                    printf("Delete operation completed.\n");
                }
                break;

            case 3:
                if (tree == NULL) {
                    printf("Tree is empty.\n");
                } else {
                    printf("Inorder Traversal: ");
                    bst_print(tree);
                    printf("\n");
                }
                break;

            case 4:
                bst_destroy(&tree);
                printf("Tree destroyed successfully.\n");
                break;

            case 5:
                bst_runTests();
                break;

            case 6:
                bst_destroy(&tree);
                printf("Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}