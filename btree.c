/*
    File: btree.c
    Easy B-Tree Implementation (Minimum degree t = 2)
    Rule: Equal values go to the RIGHT side
*/

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

/* ========== Helper: Create a new node ========== */
BTreeNode* btree_createNode(int leaf) {
    BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++)
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
BTree btree_create() {
    return btree_createNode(1);   // empty tree = one empty leaf
}

/* ============================================================
   Helper: Split a full child
   Pseudocode:
       Algorithm SplitChild(parent, i)
           y = child i of parent (full)
           Create new node z
           Move last T-1 keys of y to z
           If y is not leaf, move its last T children to z
           Insert middle key of y into parent
           Make z the new child of parent
   ============================================================ */
void btree_splitChild(BTreeNode *parent, int i) {
    BTreeNode *y = parent->children[i];
    BTreeNode *z = btree_createNode(y->leaf);
    z->n = T - 1;

    // Copy last T-1 keys from y to z
    for (int j = 0; j < T-1; j++)
        z->keys[j] = y->keys[j + T];

    // Copy children if not leaf
    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];
    }

    y->n = T - 1;

    // Shift children of parent
    for (int j = parent->n; j >= i+1; j--)
        parent->children[j+1] = parent->children[j];

    parent->children[i+1] = z;

    // Shift keys of parent
    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j+1] = parent->keys[j];

    parent->keys[i] = y->keys[T-1];
    parent->n = parent->n + 1;
}

/* ============================================================
   Helper: Insert into a non-full node
   ============================================================ */
void btree_insertNonFull(BTreeNode *node, int value) {
    int i = node->n - 1;

    if (node->leaf) {
        // Insert into leaf (shift larger keys to right)
        while (i >= 0 && value < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = value;
        node->n = node->n + 1;
    } else {
        // Find the child to go down
        while (i >= 0 && value < node->keys[i])
            i--;
        i++;

        // If child is full, split it first
        if (node->children[i]->n == 2*T - 1) {
            btree_splitChild(node, i);
            if (value > node->keys[i])
                i++;
        }
        btree_insertNonFull(node->children[i], value);
    }
}

/* ============================================================
   2. INSERT
   Pseudocode:
       Algorithm Insert(root, value)
           If root is full then
               Create new root
               Make old root its first child
               Split the old root
               Insert into the new root
           Else
               Insert into the non-full root
   ============================================================ */
void btree_insert(BTree *root, int value) {
    BTreeNode *r = *root;

    if (r->n == 2*T - 1) {          // root is full
        BTreeNode *s = btree_createNode(0);    // new root
        s->children[0] = r;
        btree_splitChild(s, 0);
        int i = 0;
        if (value > s->keys[0])
            i++;
        btree_insertNonFull(s->children[i], value);
        *root = s;
    } else {
        btree_insertNonFull(r, value);
    }
}

/* ============================================================
   3. PRINT (Inorder style traversal)
   Pseudocode:
       Algorithm Print(node)
           For i = 0 to n-1
               If not leaf → Print children[i]
               Display keys[i]
           If not leaf → Print children[n]
   ============================================================ */
void btree_print(BTree root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->n; i++) {
            if (!root->leaf)
                btree_print(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        if (!root->leaf)
            btree_print(root->children[i]);
    }
}

/* ============================================================
   4. DESTROY
   Pseudocode:
       Algorithm Destroy(node)
           If node is not NULL
               If not leaf
                   Destroy all children
               Free node
   ============================================================ */
void btree_destroy(BTree *root) {
    if (*root != NULL) {
        if (!(*root)->leaf) {
            for (int i = 0; i <= (*root)->n; i++)
                btree_destroy(&((*root)->children[i]));
        }
        free(*root);
        *root = NULL;
    }
}

/* ============================================================
   Simple Delete (for educational purpose)
   Note: Full production delete is longer; this handles
   common cases cleanly for assignment level.
   ============================================================ */
void btree_delete(BTree *root, int value) {
    // For simplicity in college ISA we provide a basic version.
    // A complete industrial delete is very long (borrow + merge).
    // This version searches and removes from leaf when possible.
    
    if (*root == NULL) return;

    BTreeNode *node = *root;
    int i = 0;
    while (i < node->n && value > node->keys[i])
        i++;

    if (i < node->n && node->keys[i] == value) {
        if (node->leaf) {
            // Remove from leaf
            for (int j = i; j < node->n - 1; j++)
                node->keys[j] = node->keys[j+1];
            node->n--;
            printf("Value %d deleted (from leaf).\n", value);
        } else {
            printf("Value found in internal node. Full delete needs merge/borrow (advanced).\n");
        }
    } else if (!node->leaf) {
        btree_delete(&(node->children[i]), value);
    } else {
        printf("Value not found.\n");
    }
}

/* ============================================================
   5. SEARCH
   ============================================================ */
int btree_search(BTree root, int value) {
    if (root == NULL) return 0;

    int i = 0;
    while (i < root->n && value > root->keys[i])
        i++;

    if (i < root->n && root->keys[i] == value)
        return 1;

    if (root->leaf)
        return 0;

    return btree_search(root->children[i], value);
}

/* ============================================================
   TEST CASES
   ============================================================ */
void btree_runTests() {
    printf("\n========== B-TREE TEST CASES ==========\n");

    BTree t = btree_create();

    printf("\nInserting: 10 20 5 6 12 30 7 17\n");
    int values[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < 8; i++)
        btree_insert(&t, values[i]);

    printf("Inorder (sorted): ");
    btree_print(t);
    printf("\n");

    printf("\nDestroying tree...\n");
    btree_destroy(&t);
    if (t == NULL)
        printf("Tree destroyed successfully!\n");

    printf("\n========== TESTS COMPLETED ==========\n");
}