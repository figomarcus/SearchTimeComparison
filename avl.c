/*
    File: avl.c
    Easy AVL Tree Implementation
    Rule: Equal values go to the RIGHT side
*/

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/* ========== Helper Functions ========== */

int height(Node *n) {
    if (n == NULL) return 0;
    return n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(Node *n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

Node* newNode(int value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;          // new node is initially at height 1
    return node;
}

/* ========== Rotations ========== */

// Right Rotation (for LL case)
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left Rotation (for RR case)
Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

/* ============================================================
   1. CREATE
   Pseudocode:
       Algorithm Create()
           Return NULL
   ============================================================ */
AVL create() {
    return NULL;
}

/* ============================================================
   2. INSERT
   Pseudocode:
       Algorithm Insert(t, value)
           If t is NULL then
               Create new node with value
               Return the new node
           End If

           If value < data of t then
               Insert in left subtree
           Else
               Insert in right subtree          // equal also goes right
           End If

           Update height of t
           Calculate balance factor

           If balance > 1 and value < left child → Right Rotate (LL)
           If balance < -1 and value > right child → Left Rotate (RR)
           If balance > 1 and value > left child → Left-Right Rotate (LR)
           If balance < -1 and value < right child → Right-Left Rotate (RL)

           Return t
   ============================================================ */
void insert(AVL *t, int value) {
    if (*t == NULL) {
        *t = newNode(value);
        return;
    }

    if (value < (*t)->data)
        insert(&((*t)->left), value);
    else
        insert(&((*t)->right), value);     // equal → right

    // Update height
    (*t)->height = 1 + max(height((*t)->left), height((*t)->right));

    int balance = getBalance(*t);

    // LL Case
    if (balance > 1 && value < (*t)->left->data)
        *t = rightRotate(*t);

    // RR Case
    else if (balance < -1 && value > (*t)->right->data)
        *t = leftRotate(*t);

    // LR Case
    else if (balance > 1 && value > (*t)->left->data) {
        (*t)->left = leftRotate((*t)->left);
        *t = rightRotate(*t);
    }

    // RL Case
    else if (balance < -1 && value < (*t)->right->data) {
        (*t)->right = rightRotate((*t)->right);
        *t = leftRotate(*t);
    }
}

/* ============================================================
   Helper: Find minimum node
   ============================================================ */
Node* findMin(Node *t) {
    while (t->left != NULL)
        t = t->left;
    return t;
}

/* ============================================================
   3. DELETE
   Pseudocode:
       Algorithm Delete(t, value)
           Normal BST delete first
           Then update height and balance
           Perform rotations if needed (same 4 cases)
   ============================================================ */
void delete(AVL *t, int value) {
    if (*t == NULL) return;

    if (value < (*t)->data)
        delete(&((*t)->left), value);
    else if (value > (*t)->data)
        delete(&((*t)->right), value);
    else {
        // Node found
        if ((*t)->left == NULL || (*t)->right == NULL) {
            Node *temp = (*t)->left ? (*t)->left : (*t)->right;
            if (temp == NULL) {
                temp = *t;
                *t = NULL;
            } else {
                **t = *temp;
            }
            free(temp);
        } else {
            Node *temp = findMin((*t)->right);
            (*t)->data = temp->data;
            delete(&((*t)->right), temp->data);
        }
    }

    if (*t == NULL) return;

    // Update height
    (*t)->height = 1 + max(height((*t)->left), height((*t)->right));

    int balance = getBalance(*t);

    // LL
    if (balance > 1 && getBalance((*t)->left) >= 0)
        *t = rightRotate(*t);

    // LR
    else if (balance > 1 && getBalance((*t)->left) < 0) {
        (*t)->left = leftRotate((*t)->left);
        *t = rightRotate(*t);
    }

    // RR
    else if (balance < -1 && getBalance((*t)->right) <= 0)
        *t = leftRotate(*t);

    // RL
    else if (balance < -1 && getBalance((*t)->right) > 0) {
        (*t)->right = rightRotate((*t)->right);
        *t = leftRotate(*t);
    }
}

/* ============================================================
   4. DESTROY
   Pseudocode:
       Algorithm Destroy(t)
           If t is not NULL then
               Destroy left
               Destroy right
               Free t
               Set t = NULL
           End If
   ============================================================ */
void destroy(AVL *t) {
    if (*t != NULL) {
        destroy(&((*t)->left));
        destroy(&((*t)->right));
        free(*t);
        *t = NULL;
    }
}

/* ============================================================
   5. PRINT (Inorder)
   Pseudocode:
       Algorithm Print(t)
           If t is not NULL then
               Print left
               Display data
               Print right
           End If
   ============================================================ */
void print(AVL t) {
    if (t != NULL) {
        print(t->left);
        printf("%d ", t->data);
        print(t->right);
    }
}

/* ============================================================
   TEST CASES
   ============================================================ */
void runTests() {
    printf("\n========== AVL TREE TEST CASES ==========\n");

    AVL t = create();

    printf("\nInserting: 10, 20, 30, 40, 50, 25\n");
    insert(&t, 10);
    insert(&t, 20);
    insert(&t, 30);
    insert(&t, 40);
    insert(&t, 50);
    insert(&t, 25);

    printf("Inorder (should be sorted): ");
    print(t);
    printf("\n");

    printf("\nDeleting 40...\n");
    delete(&t, 40);
    printf("Inorder after delete: ");
    print(t);
    printf("\n");

    printf("\nDestroying tree...\n");
    destroy(&t);
    if (t == NULL)
        printf("Tree destroyed successfully!\n");

    printf("\n========== TESTS COMPLETED ==========\n");
}