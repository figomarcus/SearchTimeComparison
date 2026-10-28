/*
    Name        : [Kiran Gavtalkar]
    Class       : [MSc AI]
    Roll Number : [2605]

    File        : btree.h
    Description : Abstract Data Type (ADT) Specification for B-Tree
*/

#ifndef BTREE_H
#define BTREE_H

#define T 2   // Minimum degree (max keys = 2*T-1 = 3)

typedef struct BTreeNode {
    int keys[2*T - 1];          // Array of keys
    struct BTreeNode *children[2*T]; // Array of child pointers
    int n;                      // Current number of keys
    int leaf;                   // 1 if leaf, 0 if internal
} BTreeNode;

typedef BTreeNode* BTree;

/* =====================================================
   ADT OPERATIONS FOR B-TREE
   ===================================================== */

/* -----------------------------------------------------
   (i) Create (btree)
   -----------------------------------------------------
   1. Function/Purpose
      To create and initialize an empty B-Tree.

   2. Pre-condition
      Sufficient memory must be available.

   3. Input
      None

   4. Output
      btree (BTree)

   5. Post-condition
      An empty B-Tree is successfully created.
----------------------------------------------------- */


/* -----------------------------------------------------
   (ii) Destroy (btree)
   -----------------------------------------------------
   1. Function/Purpose
      To destroy the B-Tree and free all memory.

   2. Pre-condition
      The B-Tree must exist.

   3. Input
      btree (BTree)

   4. Output
      btree (BTree)

   5. Post-condition
      The B-Tree no longer exists and all memory is freed.
----------------------------------------------------- */


/* -----------------------------------------------------
   (iii) Insert (btree, value)
   -----------------------------------------------------
   1. Function/Purpose
      To insert a new integer into the B-Tree while keeping
      all nodes balanced (every node has between T-1 and 2*T-1 keys).
      Equal values are inserted on the right side.

   2. Pre-condition
      The B-Tree must exist.
      Sufficient memory must be available.

   3. Input
      btree (BTree)
      value (integer)

   4. Output
      btree (BTree)

   5. Post-condition
      The value is inserted and the B-Tree remains balanced.
----------------------------------------------------- */


/* -----------------------------------------------------
   (iv) Delete (btree, value)
   -----------------------------------------------------
   1. Function/Purpose
      To remove a value from the B-Tree while keeping it balanced.

   2. Pre-condition
      The B-Tree must exist and the value must be present.

   3. Input
      btree (BTree)
      value (integer)

   4. Output
      btree (BTree)

   5. Post-condition
      The value is removed and the tree remains a valid B-Tree.
----------------------------------------------------- */


/* -----------------------------------------------------
   (v) Traverse / Print (btree)
   -----------------------------------------------------
   1. Function/Purpose
      To visit all keys in sorted order and display them.

   2. Pre-condition
      The B-Tree must exist.

   3. Input
      btree (BTree)

   4. Output
      All keys in ascending order

   5. Post-condition
      Keys are displayed; structure of the tree is unchanged.
----------------------------------------------------- */

// Function Prototypes
BTree btree_create();
void btree_insert(BTree *root, int value);
void btree_delete(BTree *root, int value);
void btree_destroy(BTree *root);
void btree_print(BTree root);
int  btree_search(BTree root, int value);
void btree_runTests();

#endif