/*
    Name        : [Your Full Name]
    Class       : [Your Class]
    Roll Number : [Your Roll Number]
    File        : bstar.h
    Description : Abstract Data Type (ADT) for B* Tree
*/

#ifndef BSTAR_H
#define BSTAR_H

#define T 3

typedef struct BStarNode {
    int keys[2*T];
    struct BStarNode *children[2*T + 1];
    int n;
    int leaf;
} BStarNode;

typedef BStarNode* BStarTree;

/* =====================================================
   ADT OPERATIONS FOR B* TREE
   ===================================================== */

/* (i) Create */
/*
1. Function/Purpose : Create an empty B* Tree
2. Pre-condition    : Sufficient memory available
3. Input            : None
4. Output           : bstar (BStarTree)
5. Post-condition   : Empty B* Tree is created
*/

/* (ii) Destroy */
/*
1. Function/Purpose : Destroy the entire B* Tree
2. Pre-condition    : Tree must exist
3. Input            : bstar (BStarTree)
4. Output           : bstar (BStarTree)
5. Post-condition   : All memory is freed
*/

/* (iii) Insert */
/*
1. Function/Purpose : Insert a value while trying to keep nodes
                      more full (idea of B* Tree)
2. Pre-condition    : Tree must exist
3. Input            : bstar (BStarTree), value (integer)
4. Output           : bstar (BStarTree)
5. Post-condition   : Value is inserted with better space utilisation
*/

/* (iv) Print */
/*
1. Function/Purpose : Print all keys in sorted order
2. Pre-condition    : Tree must exist
3. Input            : bstar (BStarTree)
4. Output           : Keys in ascending order
5. Post-condition   : Structure remains unchanged
*/

// Function Prototypes
BStarTree bstar_create();
void bstar_insert(BStarTree *root, int value);
void bstar_destroy(BStarTree *root);
void bstar_print(BStarTree root);
int  bstar_search(BStarTree root, int value);
void bstar_runTests();

#endif