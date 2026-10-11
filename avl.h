/*
    Name        : [Your Full Name]
    Class       : [Your Class]
    Roll Number : [Your Roll Number]

    File        : avl.h
    Description : Abstract Data Type (ADT) Specification for AVL Tree
*/

#ifndef AVL_H
#define AVL_H

typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

typedef AVLNode* AVL;

AVL  avl_create();
void avl_insert(AVL *t, int value);
void avl_delete(AVL *t, int value);
void avl_destroy(AVL *t);
void avl_print(AVL t);
int  avl_search(AVL t, int value);

#endif
/* =====================================================
   ADT OPERATIONS FOR AVL TREE
   ===================================================== */

/* -----------------------------------------------------
   (i) Create (avl)
   -----------------------------------------------------
   1. Function/Purpose
      To create and initialize an empty AVL Tree
      so that it is ready to store integer elements.

   2. Pre-condition
      Sufficient memory must be available.

   3. Input
      None

   4. Output
      avl (AVL)

   5. Post-condition
      An empty AVL Tree is successfully created.
----------------------------------------------------- */


/* -----------------------------------------------------
   (ii) Destroy (avl)
   -----------------------------------------------------
   1. Function/Purpose
      To destroy the AVL Tree by releasing all memory
      occupied by its nodes.

   2. Pre-condition
      The AVL Tree must exist.

   3. Input
      avl (AVL)

   4. Output
      avl (AVL)

   5. Post-condition
      The AVL Tree no longer exists.
      All memory allocated to the nodes is deallocated.
----------------------------------------------------- */


/* -----------------------------------------------------
   (iii) Insert (avl, value)
   -----------------------------------------------------
   1. Function/Purpose
      To insert a new integer element into the AVL Tree
      while keeping the tree balanced.
      Equal values are inserted on the right side.

   2. Pre-condition
      The AVL Tree must exist.
      Sufficient memory must be available.

   3. Input
      avl (AVL)
      value (integer)

   4. Output
      avl (AVL)

   5. Post-condition
      A new node is inserted at the correct position
      and the tree remains balanced (balance factor -1, 0 or 1).
----------------------------------------------------- */


/* -----------------------------------------------------
   (iv) Delete (avl, value)
   -----------------------------------------------------
   1. Function/Purpose
      To remove the specified integer element from the
      AVL Tree while keeping the tree balanced.

   2. Pre-condition
      The AVL Tree must exist.
      The tree must not be empty.
      The specified element must be present.

   3. Input
      avl (AVL)
      value (integer)

   4. Output
      avl (AVL)

   5. Post-condition
      The node is removed and the tree remains balanced.
----------------------------------------------------- */


/* -----------------------------------------------------
   (v) Traverse / Print (avl)
   -----------------------------------------------------
   1. Function/Purpose
      To visit every node using Inorder Traversal
      and display the elements in sorted order.

   2. Pre-condition
      The AVL Tree must exist.

   3. Input
      avl (AVL)

   4. Output
      Elements of the tree in ascending order

   5. Post-condition
      All elements are displayed in sorted order.
      The structure of the tree remains unchanged.
----------------------------------------------------- */