/*
    Name        : [Your Full Name]
    Class       : [Your Class]
    Roll Number : [Your Roll Number]
    File        : bplustree.h
    Description : Abstract Data Type (ADT) for B+ Tree
*/

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#define BPLUS_T 2   // Minimum degree (max keys in node = 2*BPLUS_T-1 = 3)

typedef struct BPlusNode {
    int keys[2*BPLUS_T - 1];
    struct BPlusNode *children[2*BPLUS_T];
    int n;                  // number of keys
    int leaf;               // 1 if leaf
    struct BPlusNode *next; // only used by leaf nodes (linked list)
} BPlusNode;

typedef BPlusNode* BPlusTree;

/* =====================================================
   ADT OPERATIONS FOR B+ TREE
   ===================================================== */

/* (i) Create */
/*
1. Function/Purpose : Create an empty B+ Tree
2. Pre-condition    : Sufficient memory available
3. Input            : None
4. Output           : bptree (BPlusTree)
5. Post-condition   : Empty B+ Tree is created
*/

/* (ii) Destroy */
/*
1. Function/Purpose : Destroy the entire B+ Tree
2. Pre-condition    : Tree must exist
3. Input            : bptree (BPlusTree)
4. Output           : bptree (BPlusTree)
5. Post-condition   : All memory is freed
*/

/* (iii) Insert */
/*
1. Function/Purpose : Insert a value into the B+ Tree
                      Data always goes into a leaf.
                      Equal values go to the right.
2. Pre-condition    : Tree must exist
3. Input            : bptree (BPlusTree), value (integer)
4. Output           : bptree (BPlusTree)
5. Post-condition   : Value is inserted and tree remains balanced
*/

/* (iv) Delete */
/*
1. Function/Purpose : Delete a value from a leaf of the B+ Tree
2. Pre-condition    : Tree must exist
3. Input            : bptree (BPlusTree), value (integer)
4. Output           : bptree (BPlusTree)
5. Post-condition   : Value is removed if present in a leaf
*/

/* (v) Print / Traverse */
/*
1. Function/Purpose : Print all keys by walking the leaf linked list
                      (gives sorted order)
2. Pre-condition    : Tree must exist
3. Input            : bptree (BPlusTree)
4. Output           : All keys in ascending order
5. Post-condition   : Structure remains unchanged
*/

// Function Prototypes
BPlusTree bplus_create();
void bplus_insert(BPlusTree *root, int value);
void bplus_delete(BPlusTree *root, int value);
void bplus_destroy(BPlusTree *root);
void bplus_print(BPlusTree root);
int  bplus_search(BPlusTree root, int value);
void bplus_runTests();

#endif