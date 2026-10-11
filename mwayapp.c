#include <stdio.h>
#include <stdlib.h>
#include "mway.h"

int main() {
    MWayTree tree = mway_create();
    int choice, value;

    while (1) {
        printf("\n========== m-Way Tree Menu ==========\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print (sorted)\n");
        printf("4. Destroy Tree\n");
        printf("5. Run Test Cases\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                mway_insert(&tree, value);
                printf("%d inserted.\n", value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                mway_delete(&tree, value);
                break;

            case 3:
                printf("Keys in sorted order: ");
                mway_print(tree);
                printf("\n");
                break;

            case 4:
                mway_destroy(&tree);
                tree = mway_create();
                printf("Tree destroyed.\n");
                break;

            case 5:
                mway_runTests();
                break;

            case 6:
                mway_destroy(&tree);
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}