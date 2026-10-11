#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

int main() {
    Trie root = createTrie();
    int choice;
    char key[100];

    while (1) {
        printf("\n========== Trie Menu ==========\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Destroy Trie\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%s", key);
                insertTrie(root, key);
                printf("\"%s\" inserted.\n", key);
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%s", key);
                if (searchTrie(root, key))
                    printf("\"%s\" found.\n", key);
                else
                    printf("\"%s\" not found.\n", key);
                break;

            case 3:
                destroyTrie(root);
                root = createTrie();
                printf("Trie destroyed.\n");
                break;

            case 4:
                destroyTrie(root);
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}