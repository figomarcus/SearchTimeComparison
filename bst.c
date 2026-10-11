/*
    File: bst.c
    Implementation of Binary Search Tree ADT
    Rule: Equal values go to the RIGHT side
*/

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/* ============================================================
   1. CREATE
   Pseudocode:
       Algorithm Create()
           Return NULL
   ============================================================ */
BST bst_create() {
    return NULL;
}

/* ============================================================
   2. INSERT
   Pseudocode:
       Algorithm Insert(t, value)
           If t is NULL then
               Create a new node
               Set data of new node = value
               Set left of new node = NULL
               Set right of new node = NULL
               Set t = new node
               Return
           End If

           If value < data of t then
               Insert(left of t, value)
           Else
               Insert(right of t, value)   // equal values also go right
           End If
   ============================================================ */
void bst_insert(BST *t, int value) {
    if (*t == NULL) {
        BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        *t = newNode;
        return;
    }

    if (value < (*t)->data)
        bst_insert(&((*t)->left), value);
    else
        bst_insert(&((*t)->right), value);   // equal or greater → RIGHT
}

/* ============================================================
   Helper: Find Minimum Node
   Pseudocode:
       Algorithm FindMin(t)
           While left of t is not NULL
               Set t = left of t
           End While
           Return t
   ============================================================ */
BSTNode* bst_findMin(BSTNode *t) {
    while (t->left != NULL)
        t = t->left;
    return t;
}

/* ============================================================
   3. DELETE
   Pseudocode:
       Algorithm Delete(t, value)
           If t is NULL then
               Return
           End If

           If value < data of t then
               Delete(left of t, value)
           Else If value > data of t then
               Delete(right of t, value)
           Else
               // Node found
               If t has no children then
                   Free t
                   Set t = NULL
               Else If t has only right child then
                   Set t = right of t
               Else If t has only left child then
                   Set t = left of t
               Else
                   // Two children
                   Find minimum node in right subtree
                   Copy minimum value into current node
                   Delete the minimum node from right subtree
               End If
           End If
   ============================================================ */
void bst_delete(BST *t, int value) {
    if (*t == NULL)
        return;

    if (value < (*t)->data)
        bst_delete(&((*t)->left), value);
    else if (value > (*t)->data)
        bst_delete(&((*t)->right), value);
    else {
        if ((*t)->left == NULL && (*t)->right == NULL) {
            free(*t);
            *t = NULL;
        }
        else if ((*t)->left == NULL) {
            BSTNode *temp = *t;
            *t = (*t)->right;
            free(temp);
        }
        else if ((*t)->right == NULL) {
            BSTNode *temp = *t;
            *t = (*t)->left;
            free(temp);
        }
        else {
            BSTNode *minNode = bst_findMin((*t)->right);
            (*t)->data = minNode->data;
            bst_delete(&((*t)->right), minNode->data);
        }
    }
}

/* ============================================================
   4. DESTROY
   Pseudocode:
       Algorithm Destroy(t)
           If t is not NULL then
               Destroy(left of t)
               Destroy(right of t)
               Free t
               Set t = NULL
           End If
   ============================================================ */
void bst_destroy(BST *t) {
    if (*t != NULL) {
        bst_destroy(&((*t)->left));
        bst_destroy(&((*t)->right));
        free(*t);
        *t = NULL;
    }
}

/* ============================================================
   5. PRINT (Inorder)
   Pseudocode:
       Algorithm Print(t)
           If t is not NULL then
               Print(left of t)
               Display data of t
               Print(right of t)
           End If
   ============================================================ */
void bst_print(BST t) {
    if (t != NULL) {
        bst_print(t->left);
        printf("%d ", t->data);
        bst_print(t->right);
    }
}

/* ============================================================
   6. SEARCH
   ============================================================ */
int bst_search(BST t, int value) {
    if (t == NULL) return 0;
    if (value == t->data) return 1;
    if (value < t->data)
        return bst_search(t->left, value);
    else
        return bst_search(t->right, value);
}

/* ============================================================
   ACTUAL TEST CASES
   ============================================================ */
void bst_runTests() {
    printf("\n========== RUNNING TEST CASES ==========\n");

    printf("\nTest Case 1: Insert with equal values + Print\n");
    BST t = bst_create();
    bst_insert(&t, 50);
    bst_insert(&t, 30);
    bst_insert(&t, 70);
    bst_insert(&t, 50);     // equal → goes right
    bst_insert(&t, 30);     // equal → goes right
    bst_insert(&t, 20);
    bst_insert(&t, 40);

    printf("Inorder Traversal: ");
    bst_print(t);
    printf("\n");       // Expected: 20 30 30 40 50 50 70

    printf("\nTest Case 2: Delete 30\n");
    bst_delete(&t, 30);
    printf("After deleting 30: ");
    bst_print(t);
    printf("\n");

    printf("\nTest Case 3: Delete 50\n");
    bst_delete(&t, 50);
    printf("After deleting 50: ");
    bst_print(t);
    printf("\n");

    printf("\nTest Case 4: Destroy the tree\n");
    bst_destroy(&t);
    if (t == NULL)
        printf("Tree destroyed successfully!\n");

    printf("\n========== ALL TESTS COMPLETED ==========\n");
}
