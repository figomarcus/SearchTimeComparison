#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main() {
    AVL tree = avl_create();
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
                avl_insert(&tree, value);
                printf("%d inserted (tree is balanced).\n", value);
                break;

            case 2:
                if (tree == NULL)
                    printf("Tree is empty.\n");
                else {
                    printf("Enter value to delete: ");
                    scanf("%d", &value);
                    avl_delete(&tree, value);
                    printf("Delete completed.\n");
                }
                break;

            case 3:
                if (tree == NULL)
                    printf("Tree is empty.\n");
                else {
                    printf("Inorder Traversal: ");
                    avl_print(tree);
                    printf("\n");
                }
                break;

            case 4:
                avl_destroy(&tree);
                printf("Tree destroyed.\n");
                break;

            case 5:
                avl_runTests();
                break;

            case 6:
                avl_destroy(&tree);
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}