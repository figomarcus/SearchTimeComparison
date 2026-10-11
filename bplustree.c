/*
    File: bplustree.c
    Easy B+ Tree (t = 2)
    All data stored only in leaves + leaves are linked
*/

#include <stdio.h>
#include <stdlib.h>
#include "bplustree.h"

/* Create a new node */
BPlusNode* bplus_createNode(int leaf) {
    BPlusNode *node = (BPlusNode*)malloc(sizeof(BPlusNode));
    node->n = 0;
    node->leaf = leaf;
    node->next = NULL;
    for (int i = 0; i < 2*BPLUS_T; i++)
        node->children[i] = NULL;
    return node;
}

/* ============================================================
   1. CREATE
   Pseudocode:
       Algorithm Create()
           Create an empty leaf node
           Return it as root
   ============================================================ */
BPlusTree bplus_create() {
    return bplus_createNode(1);
}

/* Split a full child (used during insertion) */
void bplus_splitChild(BPlusNode *parent, int i) {
    BPlusNode *y = parent->children[i];
    BPlusNode *z = bplus_createNode(y->leaf);
    z->n = BPLUS_T - 1;

    // Copy keys
    for (int j = 0; j < BPLUS_T-1; j++)
        z->keys[j] = y->keys[j + BPLUS_T];

    // If not leaf, copy children
    if (!y->leaf) {
        for (int j = 0; j < BPLUS_T; j++)
            z->children[j] = y->children[j + BPLUS_T];
    } else {
        // Important for B+ : link the leaves
        z->next = y->next;
        y->next = z;
    }

    y->n = BPLUS_T - 1;

    // Shift parent's children
    for (int j = parent->n; j >= i+1; j--)
        parent->children[j+1] = parent->children[j];
    parent->children[i+1] = z;

    // Shift parent's keys and insert middle key
    for (int j = parent->n-1; j >= i; j--)
        parent->keys[j+1] = parent->keys[j];

    parent->keys[i] = y->keys[BPLUS_T-1];   // separator key goes up
    parent->n++;
}

/* Insert into a non-full node */
void bplus_insertNonFull(BPlusNode *node, int value) {
    int i = node->n - 1;

    if (node->leaf) {
        // Insert into leaf in sorted order
        while (i >= 0 && value < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = value;
        node->n++;
    } else {
        // Find the correct child
        while (i >= 0 && value < node->keys[i])
            i--;
        i++;

        if (node->children[i]->n == 2*BPLUS_T - 1) {
            bplus_splitChild(node, i);
            if (value > node->keys[i])
                i++;
        }
        bplus_insertNonFull(node->children[i], value);
    }
}

/* ============================================================
   2. INSERT
   Pseudocode:
       Algorithm Insert(root, value)
           If root is full
               Create new root
               Make old root its child
               Split the old root
           Insert the value into a leaf
   ============================================================ */
void bplus_insert(BPlusTree *root, int value) {
    BPlusNode *r = *root;

    if (r->n == 2*BPLUS_T - 1) {
        BPlusNode *s = bplus_createNode(0);          // new root (internal)
        s->children[0] = r;
        bplus_splitChild(s, 0);

        int i = 0;
        if (value > s->keys[0])
            i++;
        bplus_insertNonFull(s->children[i], value);
        *root = s;
    } else {
        bplus_insertNonFull(r, value);
    }
}

/* ============================================================
   3. PRINT
   Pseudocode:
       Algorithm Print(root)
           Go to the leftmost leaf
           Walk the leaf linked list and print all keys
   ============================================================ */
void bplus_print(BPlusTree root) {
    if (root == NULL) return;

    // Go to the leftmost leaf
    BPlusNode *node = root;
    while (!node->leaf)
        node = node->children[0];

    // Walk the leaf linked list
    printf("Leaf sequence: ");
    while (node != NULL) {
        for (int i = 0; i < node->n; i++)
            printf("%d ", node->keys[i]);
        node = node->next;
    }
    printf("\n");
}

/* ============================================================
   4. DESTROY
   ============================================================ */
void bplus_destroy(BPlusTree *root) {
    if (*root == NULL) return;

    if (!(*root)->leaf) {
        for (int i = 0; i <= (*root)->n; i++)
            bplus_destroy(&((*root)->children[i]));
    }
    free(*root);
    *root = NULL;
}

/* ============================================================
   5. DELETE (basic version – removes from leaf only)
   ============================================================ */
void bplus_delete(BPlusTree *root, int value) {
    if (*root == NULL) return;

    // Find the leaf that should contain the value
    BPlusNode *node = *root;
    while (!node->leaf) {
        int i = 0;
        while (i < node->n && value >= node->keys[i])
            i++;
        node = node->children[i];
    }

    // Search inside the leaf
    int i = 0;
    while (i < node->n && node->keys[i] < value)
        i++;

    if (i < node->n && node->keys[i] == value) {
        for (int j = i; j < node->n-1; j++)
            node->keys[j] = node->keys[j+1];
        node->n--;
        printf("%d deleted from leaf.\n", value);
    } else {
        printf("Value not found in any leaf.\n");
    }
}

/* ============================================================
   6. SEARCH
   ============================================================ */
int bplus_search(BPlusTree root, int value) {
    if (root == NULL) return 0;

    BPlusNode *node = root;
    while (!node->leaf) {
        int i = 0;
        while (i < node->n && value >= node->keys[i])
            i++;
        node = node->children[i];
    }

    for (int i = 0; i < node->n; i++) {
        if (node->keys[i] == value)
            return 1;
    }
    return 0;
}

/* ============================================================
   TEST CASES
   ============================================================ */
void bplus_runTests() {
    printf("\n========== B+ TREE TEST CASES ==========\n");

    BPlusTree t = bplus_create();

    printf("Inserting: 10, 20, 5, 15, 25, 30, 7, 17\n");
    int vals[] = {10, 20, 5, 15, 25, 30, 7, 17};
    for (int i = 0; i < 8; i++)
        bplus_insert(&t, vals[i]);

    bplus_print(t);

    printf("\nDeleting 15...\n");
    bplus_delete(&t, 15);
    bplus_print(t);

    bplus_destroy(&t);
    printf("Tree destroyed successfully.\n");
    printf("========== TESTS COMPLETED ==========\n");
}