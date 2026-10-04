/*
    File: mway.c
    Easy m-Way Search Tree (m = 3)
    Rule: Equal values go to the RIGHT
*/

#include <stdio.h>
#include <stdlib.h>
#include "mway.h"

/* Create a new node */
Node* createNode(int leaf) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->n = 0;
    node->leaf = leaf;
    for (int i = 0; i < M; i++)
        node->children[i] = NULL;
    return node;
}

/* ============================================================
   1. CREATE
   Pseudocode:
       Algorithm Create()
           Create a new empty leaf node
           Return it as root
   ============================================================ */
MWayTree create() {
    return createNode(1);
}

/* ============================================================
   2. INSERT
   Pseudocode:
       Algorithm Insert(root, value)
           If root is NULL → create new node
           Find the correct child index
           If current node is leaf
               If space available → insert key in sorted order
               Else create a new leaf child and insert there
           Else
               Recursively insert in the correct child
   ============================================================ */
void insert(MWayTree *root, int value) {
    if (*root == NULL) {
        *root = createNode(1);
        (*root)->keys[0] = value;
        (*root)->n = 1;
        return;
    }

    Node *node = *root;

    // Find the correct position / child
    int i = 0;
    while (i < node->n && value >= node->keys[i])  // equal goes right
        i++;

    if (node->leaf) {
        if (node->n < M-1) {
            // Space available – insert in sorted order
            for (int j = node->n; j > i; j--)
                node->keys[j] = node->keys[j-1];
            node->keys[i] = value;
            node->n++;
        } else {
            // Node full – create a new leaf child (tree can become unbalanced)
            Node *newChild = createNode(1);
            newChild->keys[0] = value;
            newChild->n = 1;
            node->children[i] = newChild;
            node->leaf = 0;  // now it becomes internal
        }
    } else {
        // Go down to the correct child
        if (node->children[i] == NULL) {
            node->children[i] = createNode(1);
            node->children[i]->keys[0] = value;
            node->children[i]->n = 1;
        } else {
            insert(&(node->children[i]), value);
        }
    }
}

/* ============================================================
   3. PRINT (sorted order)
   Pseudocode:
       Algorithm Print(node)
           For i = 0 to n-1
               Print children[i]
               Display keys[i]
           Print children[n]
   ============================================================ */
void print(MWayTree root) {
    if (root == NULL) return;

    int i;
    for (i = 0; i < root->n; i++) {
        print(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    print(root->children[i]);
}

/* ============================================================
   4. DESTROY
   Pseudocode:
       Algorithm Destroy(node)
           If node is not NULL
               Destroy all children
               Free node
   ============================================================ */
void destroy(MWayTree *root) {
    if (*root != NULL) {
        for (int i = 0; i <= (*root)->n; i++)
            destroy(&((*root)->children[i]));
        free(*root);
        *root = NULL;
    }
}

/* ============================================================
   5. DELETE (simple version – removes from leaf)
   ============================================================ */
void delete(MWayTree *root, int value) {
    if (*root == NULL) return;

    Node *node = *root;
    int i = 0;
    while (i < node->n && value > node->keys[i])
        i++;

    if (i < node->n && node->keys[i] == value) {
        if (node->leaf) {
            // Remove from leaf
            for (int j = i; j < node->n-1; j++)
                node->keys[j] = node->keys[j+1];
            node->n--;
            printf("%d deleted from leaf.\n", value);
        } else {
            printf("Value is in internal node (simple version skips full internal delete).\n");
        }
    } else if (!node->leaf && node->children[i] != NULL) {
        delete(&(node->children[i]), value);
    } else {
        printf("Value not found.\n");
    }
}

/* ============================================================
   TEST CASES
   ============================================================ */
void runTests() {
    printf("\n========== m-WAY TREE TEST CASES ==========\n");

    MWayTree t = create();

    printf("Inserting: 10, 20, 5, 15, 30, 25, 8\n");
    int vals[] = {10, 20, 5, 15, 30, 25, 8};
    for (int i = 0; i < 7; i++)
        insert(&t, vals[i]);

    printf("Keys in sorted order: ");
    print(t);
    printf("\n");

    destroy(&t);
    printf("Tree destroyed successfully.\n");
    printf("========== TESTS COMPLETED ==========\n");
}