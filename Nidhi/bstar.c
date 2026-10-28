/*
    Name        : [Nidhi Nagvenkar]
    Class       : [MSc AI]
    Roll Number : [2606]
    File        : bstar.h
    Description : Abstract Data Type (ADT) for B* Tree
    Date Created: 30/09/26
    Date Modified: 30/09/26
*/

#include <stdio.h>
#include <stdlib.h>
#include "bstar.h"

/* Create a new node */
BStarNode* bstar_createNode(int leaf) {
    BStarNode *node = (BStarNode*)malloc(sizeof(BStarNode));
    node->n = 0;
    node->leaf = leaf;
    for (int i = 0; i <= 2*BSTAR_T; i++)
        node->children[i] = NULL;
    return node;
}

/*
1. Create(bstar)

Function:
    Creates an empty B* Tree.

Pseudocode:
    1. Check whether tree exists.
    2. Set root to NULL.
    3. Return.
*/
BStarTree bstar_create() {
    return bstar_createNode(1);
}

/* Split child */
void bstar_splitChild(BStarNode *parent, int i) {
    BStarNode *y = parent->children[i];
    BStarNode *z = bstar_createNode(y->leaf);
    int mid = y->n / 2;

    z->n = y->n - mid - 1;

    for (int j = 0; j < z->n; j++)
        z->keys[j] = y->keys[mid + 1 + j];

    if (!y->leaf) {
        for (int j = 0; j <= z->n; j++)
            z->children[j] = y->children[mid + 1 + j];
    }

    y->n = mid;

    for (int j = parent->n; j > i; j--) {
        parent->keys[j] = parent->keys[j-1];
        parent->children[j+1] = parent->children[j];
    }

    parent->keys[i] = y->keys[mid];
    parent->children[i+1] = z;
    parent->n++;
}

/* Insert into a non-full node */
void bstar_insertNonFull(BStarNode *node, int value) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && value < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = value;
        node->n++;
    } else {
        while (i >= 0 && value < node->keys[i])
            i--;
        i++;

        if (node->children[i]->n == 2*BSTAR_T) {
            bstar_splitChild(node, i);
            if (value > node->keys[i])
                i++;
        }
        bstar_insertNonFull(node->children[i], value);
    }
}

/*
3. InsertElement(bstar, new.element)

Function:
    Inserts a new integer element into the B* Tree.

Pseudocode:
    1. Check tree and element.
    2. If tree is empty:
         Create root.
         Insert element.
    3. Otherwise recursively insert element.
    4. If root splits:
         Create new root.
    5. Return flag.
*/
void bstar_insert(BStarTree *root, int value) {
    BStarNode *r = *root;

    if (r->n == 2*BSTAR_T) {
        BStarNode *s = bstar_createNode(0);
        s->children[0] = r;
        bstar_splitChild(s, 0);

        int i = 0;
        if (value > s->keys[0])
            i++;
        bstar_insertNonFull(s->children[i], value);
        *root = s;
    } else {
        bstar_insertNonFull(r, value);
    }
}

/* ============================================================
   3. PRINT

   Algorithm bstar_print(root)
    If root is not NULL then
        For i = 0 to n-1
            If root is not leaf then
                bstar_print(children[i])
            End If
            Display keys[i]
        End For
        If root is not leaf then
            bstar_print(children[n])
        End If
    End If
   ============================================================ */
void bstar_print(BStarTree root) {
    if (root == NULL) return;

    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            bstar_print(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        bstar_print(root->children[i]);
}

/*
2. Destroy(bstar)

Function:
    Deletes the complete B* Tree and releases all allocated memory.

Pseudocode:
    1. If tree is NULL, return.
    2. Recursively visit all child nodes.
    3. Free every node.
    4. Set root to NULL.
*/
void bstar_destroy(BStarTree *root) {
    if (*root == NULL) return;

    if (!(*root)->leaf) {
        for (int i = 0; i <= (*root)->n; i++)
            bstar_destroy(&((*root)->children[i]));
    }
    free(*root);
    *root = NULL;
}

/*
6. Search(bstar, search.element)

Function:
    Searches for a specified element in the B* Tree.

Pseudocode:
    1. Check whether tree exists.
    2. Start searching from root.
    3. Compare keys.
    4. Move to appropriate child.
    5. Return flag.
*/
int bstar_search(BStarTree root, int value) {
    if (root == NULL) return 0;

    int i = 0;
    while (i < root->n && value > root->keys[i])
        i++;

    if (i < root->n && root->keys[i] == value)
        return 1;

    if (root->leaf)
        return 0;

    return bstar_search(root->children[i], value);
}

/* ============================================================
   TEST CASES
   ============================================================ */
void bstar_runTests() {
    printf("\n========== B* TREE TEST CASES ==========\n");

    BStarTree t = bstar_create();

    printf("Inserting: 10 20 5 6 12 30 7 17 25 15\n");
    int vals[] = {10, 20, 5, 6, 12, 30, 7, 17, 25, 15};
    for (int i = 0; i < 10; i++)
        bstar_insert(&t, vals[i]);

    printf("Inorder: ");
    bstar_print(t);
    printf("\n");

    bstar_destroy(&t);
    printf("Tree destroyed successfully.\n");
    printf("========== TESTS COMPLETED ==========\n");
}