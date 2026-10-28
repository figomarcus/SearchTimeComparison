/*
    Name        : [Figo Marcus Fernandes]
    Class       : [MSc AI Part 1]
    Roll Number : [2604]

    File        : mway.h
    Description : Abstract Data Type (ADT) Specification for Mway Tree
*/


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
/*
=====================================================
ADT SPECIFICATION FOR m-WAY TREE
=====================================================

(i) Create (mway)
1. Function/Purpose
   To create and initialize an empty m-Way Tree.
2. Pre-condition
   Sufficient memory must be available.
3. Input
   None
4. Output
   mway (MWayTree)
5. Post-condition
   An empty m-Way Tree is successfully created.

(ii) Insert (mway, value)
1. Function/Purpose
   To insert an integer into the m-Way Tree.
   Equal values go to the right side.
2. Pre-condition
   The m-Way Tree must exist.
   Sufficient memory must be available.
3. Input
   mway (MWayTree)
   value (integer)
4. Output
   mway (MWayTree)
5. Post-condition
   The value is inserted at the correct position.
   Tree may become unbalanced.

(iii) Delete (mway, value)
1. Function/Purpose
   To delete a value from the m-Way Tree.
2. Pre-condition
   The m-Way Tree must exist.
3. Input
   mway (MWayTree)
   value (integer)
4. Output
   mway (MWayTree)
5. Post-condition
   The value is removed if found (simple version removes from leaf).

(iv) Search (mway, value)
1. Function/Purpose
   To search for a value in the m-Way Tree.
2. Pre-condition
   The m-Way Tree must exist.
3. Input
   mway (MWayTree)
   value (integer)
4. Output
   flag (boolean)   // 1 if found, 0 if not found
5. Post-condition
   Structure of the tree remains unchanged.

(v) Destroy (mway)
1. Function/Purpose
   To destroy the entire m-Way Tree and free all memory.
2. Pre-condition
   The m-Way Tree must exist.
3. Input
   mway (MWayTree)
4. Output
   mway (MWayTree)
5. Post-condition
   All nodes are freed and the tree becomes empty.

(vi) Print (mway)
1. Function/Purpose
   To print all keys of the m-Way Tree in sorted order.
2. Pre-condition
   The m-Way Tree must exist.
3. Input
   mway (MWayTree)
4. Output
   Keys in ascending order
5. Post-condition
   Structure of the tree remains unchanged.
=====================================================
*/