/*
    File: avlapp.c
    Menu driven program for AVL Tree
*/

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main() {
    AVL tree = create();
    int choice, value;

    while (1) {
        printf("\n========== AVL Tree Menu ==========\n");
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
                insert(&tree, value);
                printf("%d inserted (tree is balanced).\n", value);
                break;

            case 2:
                if (tree == NULL)
                    printf("Tree is empty.\n");
                else {
                    printf("Enter value to delete: ");
                    scanf("%d", &value);
                    delete(&tree, value);
                    printf("Delete completed (tree remains balanced).\n");
                }
                break;

            case 3:
                if (tree == NULL)
                    printf("Tree is empty.\n");
                else {
                    printf("Inorder Traversal: ");
                    print(tree);
                    printf("\n");
                }
                break;

            case 4:
                destroy(&tree);
                printf("Tree destroyed.\n");
                break;

            case 5:
                runTests();
                break;

            case 6:
                destroy(&tree);
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}