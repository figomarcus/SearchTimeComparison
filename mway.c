#include <stdio.h>
#include <stdlib.h>
#include "mway.h"

MWayNode* mway_createNode(int leaf) {
    MWayNode *node = (MWayNode*)malloc(sizeof(MWayNode));
    node->n = 0;
    node->leaf = leaf;
    for (int i = 0; i < M; i++)
        node->children[i] = NULL;
    return node;
}

MWayTree mway_create() {
    return mway_createNode(1);
}

void mway_insert(MWayTree *root, int value) {
    if (*root == NULL) {
        *root = mway_createNode(1);
        (*root)->keys[0] = value;
        (*root)->n = 1;
        return;
    }

    MWayNode *node = *root;
    int i = 0;
    while (i < node->n && value >= node->keys[i])
        i++;

    if (node->leaf) {
        if (node->n < M-1) {
            for (int j = node->n; j > i; j--)
                node->keys[j] = node->keys[j-1];
            node->keys[i] = value;
            node->n++;
        } else {
            MWayNode *newChild = mway_createNode(1);
            newChild->keys[0] = value;
            newChild->n = 1;
            node->children[i] = newChild;
            node->leaf = 0;
        }
    } else {
        if (node->children[i] == NULL) {
            node->children[i] = mway_createNode(1);
            node->children[i]->keys[0] = value;
            node->children[i]->n = 1;
        } else {
            mway_insert(&(node->children[i]), value);
        }
    }
}

int mway_search(MWayTree root, int value) {
    if (root == NULL) return 0;

    int i = 0;
    while (i < root->n && value > root->keys[i])
        i++;

    if (i < root->n && root->keys[i] == value)
        return 1;

    if (root->leaf)
        return 0;

    return mway_search(root->children[i], value);
}

void mway_print(MWayTree root) {
    if (root == NULL) return;

    int i;
    for (i = 0; i < root->n; i++) {
        mway_print(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    mway_print(root->children[i]);
}

void mway_destroy(MWayTree *root) {
    if (*root != NULL) {
        for (int i = 0; i <= (*root)->n; i++)
            mway_destroy(&((*root)->children[i]));
        free(*root);
        *root = NULL;
    }
}

void mway_delete(MWayTree *root, int value) {
    if (*root == NULL) return;

    MWayNode *node = *root;
    int i = 0;
    while (i < node->n && value > node->keys[i])
        i++;

    if (i < node->n && node->keys[i] == value) {
        if (node->leaf) {
            for (int j = i; j < node->n-1; j++)
                node->keys[j] = node->keys[j+1];
            node->n--;
            printf("%d deleted from leaf.\n", value);
        } else {
            printf("Value is in internal node (simple version).\n");
        }
    } else if (!node->leaf && node->children[i] != NULL) {
        mway_delete(&(node->children[i]), value);
    } else {
        printf("Value not found.\n");
    }
}

void mway_runTests() {
    printf("\n========== m-WAY TREE TEST CASES ==========\n");

    MWayTree t = mway_create();

    printf("Inserting: 10, 20, 5, 15, 30, 25, 8\n");
    int vals[] = {10, 20, 5, 15, 30, 25, 8};
    for (int i = 0; i < 7; i++)
        mway_insert(&t, vals[i]);

    printf("Keys in sorted order: ");
    mway_print(t);
    printf("\n");

    mway_destroy(&t);
    printf("Tree destroyed successfully.\n");
    printf("========== TESTS COMPLETED ==========\n");
}