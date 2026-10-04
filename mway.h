/*
    Name        : [Figo Marcus Fernandes]
    Class       : [MSc AI]
    Roll Number : [2604]

    File        : mway.h
    Description : Abstract Data Type (ADT) for m-Way Search Tree
*/

#ifndef MWAY_H
#define MWAY_H

#define M 3   // Order of the tree (max children = 3, max keys = 2)

typedef struct Node {
    int keys[M-1];              // Maximum M-1 keys
    struct Node *children[M];   // Maximum M children
    int n;                      // Current number of keys
    int leaf;                   // 1 = leaf, 0 = internal
} Node;

typedef Node* MWayTree;

/* =====================================================
   ADT OPERATIONS FOR m-WAY TREE
   ===================================================== */

/* (i) Create */
/*
1. Function/Purpose : Create an empty m-Way Tree
2. Pre-condition    : Sufficient memory available
3. Input            : None
4. Output           : mway (MWayTree)
5. Post-condition   : Empty m-Way Tree is created
*/

/* (ii) Destroy */
/*
1. Function/Purpose : Destroy the entire m-Way Tree
2. Pre-condition    : Tree must exist
3. Input            : mway (MWayTree)
4. Output           : mway (MWayTree)
5. Post-condition   : All memory is freed, tree becomes empty
*/

/* (iii) Insert */
/*
1. Function/Purpose : Insert an integer into the m-Way Tree
                      Equal values go to the right
2. Pre-condition    : Tree must exist
3. Input            : mway (MWayTree), value (integer)
4. Output           : mway (MWayTree)
5. Post-condition   : Value is inserted (tree may become unbalanced)
*/

/* (iv) Delete */
/*
1. Function/Purpose : Delete a value from the m-Way Tree
2. Pre-condition    : Tree must exist and value should be present
3. Input            : mway (MWayTree), value (integer)
4. Output           : mway (MWayTree)
5. Post-condition   : Value is removed if found
*/

/* (v) Print / Traverse */
/*
1. Function/Purpose : Print all keys in sorted order
2. Pre-condition    : Tree must exist
3. Input            : mway (MWayTree)
4. Output           : Keys in ascending order
5. Post-condition   : Structure of tree remains unchanged
*/

// Function Prototypes
MWayTree create();
void insert(MWayTree *root, int value);
void delete(MWayTree *root, int value);
void destroy(MWayTree *root);
void print(MWayTree root);
void runTests();

#endif