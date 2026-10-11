/*
    Name        : [Your Full Name]
    Class       : [Your Class]
    Roll Number : [Your Roll Number]

    File        : bst.h
    Description : Abstract Data Type (ADT) Specification for Binary Search Tree
*/

#ifndef BST_H
#define BST_H

typedef struct BSTNode {
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef BSTNode* BST;

/* =====================================================
   ADT OPERATIONS FOR BINARY SEARCH TREE
   ===================================================== */

/* -----------------------------------------------------
   (i) Create (bst)
   -----------------------------------------------------
   1. Function/Purpose
      To create and initialize an empty Binary Search Tree
      so that it is ready to store integer elements.

   2. Pre-condition
      Sufficient memory must be available.

   3. Input
      None

   4. Output
      bst (BST)

   5. Post-condition
      An empty Binary Search Tree is successfully created.
----------------------------------------------------- */


/* -----------------------------------------------------
   (ii) Destroy (bst)
   -----------------------------------------------------
   1. Function/Purpose
      To destroy the Binary Search Tree by releasing all
      memory occupied by its nodes.

   2. Pre-condition
      The Binary Search Tree must exist.

   3. Input
      bst (BST)

   4. Output
      bst (BST)

   5. Post-condition
      The Binary Search Tree no longer exists.
      All memory allocated to the nodes is deallocated.
      The tree cannot be accessed unless it is created again.
----------------------------------------------------- */


/* -----------------------------------------------------
   (iii) Insert (bst, value)
   -----------------------------------------------------
   1. Function/Purpose
      To insert a new integer element into the Binary Search Tree.
      If the value is equal to an existing node, it is placed
      on the right side of that node.

   2. Pre-condition
      The Binary Search Tree must exist.
      Sufficient memory must be available for creating a new node.

   3. Input
      bst (BST)
      value (integer)

   4. Output
      bst (BST)

   5. Post-condition
      A new node containing the given value is inserted at the
      correct position. Equal values are inserted on the right side.
----------------------------------------------------- */


/* -----------------------------------------------------
   (iv) Delete (bst, value)
   -----------------------------------------------------
   1. Function/Purpose
      To remove the specified integer element from the
      Binary Search Tree.

   2. Pre-condition
      The Binary Search Tree must exist.
      The tree must not be empty.
      The specified element must be present in the tree.

   3. Input
      bst (BST)
      value (integer)

   4. Output
      bst (BST)

   5. Post-condition
      The specified node is removed from the tree,
      its memory is deallocated, and the BST property is maintained.
----------------------------------------------------- */


/* -----------------------------------------------------
   (v) Traverse / Print (bst)
   -----------------------------------------------------
   1. Function/Purpose
      To visit every node of the Binary Search Tree using
      Inorder Traversal and display the elements in sorted order.

   2. Pre-condition
      The Binary Search Tree must exist.

   3. Input
      bst (BST)

   4. Output
      Elements of the tree in ascending order

   5. Post-condition
      All elements are displayed in sorted order.
      The structure of the tree remains unchanged.
----------------------------------------------------- */

// Function Prototypes
BST  bst_create();
void bst_insert(BST *t, int value);
void bst_delete(BST *t, int value);
void bst_destroy(BST *t);
void bst_print(BST t);
int  bst_search(BST t, int value);
void bst_runTests();

#endif