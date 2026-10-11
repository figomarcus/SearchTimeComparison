#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/* ===== Helper Functions ===== */

int avl_height(AVLNode *n) {
    if (n == NULL) return 0;
    return n->height;
}

int avl_max(int a, int b) {
    return (a > b) ? a : b;
}

int avl_getBalance(AVLNode *n) {
    if (n == NULL) return 0;
    return avl_height(n->left) - avl_height(n->right);
}

AVLNode* avl_newNode(int value) {
    AVLNode *node = malloc(sizeof(AVLNode));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    node->data = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

/* ===== Rotations ===== */

AVLNode* avl_rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = avl_max(avl_height(y->left), avl_height(y->right)) + 1;
    x->height = avl_max(avl_height(x->left), avl_height(x->right)) + 1;

    return x;
}

AVLNode* avl_leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = avl_max(avl_height(x->left), avl_height(x->right)) + 1;
    y->height = avl_max(avl_height(y->left), avl_height(y->right)) + 1;

    return y;
}

/* ===== CREATE ===== */
AVL avl_create() {
    return NULL;
}


void avl_insert(AVL *t, int value) {
    if (*t == NULL) {
        *t = avl_newNode(value);

        if (*t == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        return;
    }

    if (value < (*t)->data)
        avl_insert(&((*t)->left), value);
    else
        avl_insert(&((*t)->right), value);

    (*t)->height =
        1 + avl_max(avl_height((*t)->left),
                    avl_height((*t)->right));

    int balance = avl_getBalance(*t);

    // Left-Left
    if (balance > 1 && value < (*t)->left->data) {
        *t = avl_rightRotate(*t);
    }
    // Right-Right, including duplicate values
    else if (balance < -1 && value >= (*t)->right->data) {
        *t = avl_leftRotate(*t);
    }
    // Left-Right
    else if (balance > 1 && value >= (*t)->left->data) {
        (*t)->left = avl_leftRotate((*t)->left);
        *t = avl_rightRotate(*t);
    }
    // Right-Left
    else if (balance < -1 && value < (*t)->right->data) {
        (*t)->right = avl_rightRotate((*t)->right);
        *t = avl_leftRotate(*t);
    }
}


/* ===== Helper for Delete ===== */
AVLNode* avl_findMin(AVLNode *t) {
    while (t->left != NULL)
        t = t->left;
    return t;
}

/* ===== DELETE ===== */
void avl_delete(AVL *t, int value) {
    if (*t == NULL) return;

    if (value < (*t)->data)
        avl_delete(&((*t)->left), value);
    else if (value > (*t)->data)
        avl_delete(&((*t)->right), value);
    else {
        if ((*t)->left == NULL || (*t)->right == NULL) {
            AVLNode *temp = (*t)->left ? (*t)->left : (*t)->right;
            if (temp == NULL) {
                temp = *t;
                *t = NULL;
            } else {
                **t = *temp;
            }
            free(temp);
        } else {
            AVLNode *temp = avl_findMin((*t)->right);
            (*t)->data = temp->data;
            avl_delete(&((*t)->right), temp->data);
        }
    }

    if (*t == NULL) return;

    (*t)->height = 1 + avl_max(avl_height((*t)->left), avl_height((*t)->right));
    int balance = avl_getBalance(*t);

    if (balance > 1 && avl_getBalance((*t)->left) >= 0)
        *t = avl_rightRotate(*t);
    else if (balance > 1 && avl_getBalance((*t)->left) < 0) {
        (*t)->left = avl_leftRotate((*t)->left);
        *t = avl_rightRotate(*t);
    }
    else if (balance < -1 && avl_getBalance((*t)->right) <= 0)
        *t = avl_leftRotate(*t);
    else if (balance < -1 && avl_getBalance((*t)->right) > 0) {
        (*t)->right = avl_rightRotate((*t)->right);
        *t = avl_leftRotate(*t);
    }
}

/* ===== DESTROY ===== */
void avl_destroy(AVL *t) {
    if (*t != NULL) {
        avl_destroy(&((*t)->left));
        avl_destroy(&((*t)->right));
        free(*t);
        *t = NULL;
    }
}

/* ===== PRINT ===== */
void avl_print(AVL t) {
    if (t != NULL) {
        avl_print(t->left);
        printf("%d ", t->data);
        avl_print(t->right);
    }
}

/* ===== SEARCH ===== */
int avl_search(AVL t, int value) {
    if (t == NULL) return 0;
    if (value == t->data) return 1;
    if (value < t->data)
        return avl_search(t->left, value);
    else
        return avl_search(t->right, value);
}

/* ===== TEST CASES ===== */
void avl_runTests() {
    printf("\n========== AVL TREE TEST CASES ==========\n");

    AVL t = avl_create();

    printf("Inserting: 10, 20, 30, 40, 50, 25\n");
    avl_insert(&t, 10);
    avl_insert(&t, 20);
    avl_insert(&t, 30);
    avl_insert(&t, 40);
    avl_insert(&t, 50);
    avl_insert(&t, 25);

    printf("Inorder: ");
    avl_print(t);
    printf("\n");

    printf("Deleting 40...\n");
    avl_delete(&t, 40);
    printf("Inorder after delete: ");
    avl_print(t);
    printf("\n");

    avl_destroy(&t);
    printf("Tree destroyed successfully!\n");
    printf("========== TESTS COMPLETED ==========\n");
}