#ifndef MWAY_H
#define MWAY_H

#define M 3

typedef struct MWayNode {
    int keys[M-1];
    struct MWayNode *children[M];
    int n;
    int leaf;
} MWayNode;

typedef MWayNode* MWayTree;

MWayTree mway_create();
void mway_insert(MWayTree *root, int value);
void mway_delete(MWayTree *root, int value);
void mway_destroy(MWayTree *root);
void mway_print(MWayTree root);
int  mway_search(MWayTree root, int value);
void mway_runTests();

#endif