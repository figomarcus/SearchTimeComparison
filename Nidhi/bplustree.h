/*
    Name        : [Nidhi Nagvenkar]
    Class       : [MSc AI]
    Roll Number : [2606]
    File        : bplustree.h
    Description : Abstract Data Type (ADT) for B+ Tree
    Date Created: 30/09/26
    Date Modified: 30/09/26
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

/* 

(a) Structure:
A B+ Tree is a dynamic multi-way search tree in which all actual
data elements are stored in the leaf nodes. The internal nodes
contain keys used for searching and directing the search.

For every B+ Tree:
- All leaf nodes are at the same level.
- All actual elements are stored in leaf nodes.
- Internal nodes contain separator keys.
- Leaf nodes are connected using a next pointer.
- The keys in every node are maintained in sorted order.
- Duplicate elements can be inserted.
- ORDER represents the maximum number of children.
- Maximum number of keys in a node is ORDER - 1.

For this implementation:
ORDER = 4
Maximum children = 4
Maximum keys = 3

(b) Operations:
(i)   Create(bplus)
(ii)  Destroy(bplus)
(iii) InsertElement(bplus, new.element)
(iv)  DeleteElement(bplus, delete.element)
(v)   TraverseElement(bplus)
(vi)  Search(bplus, search.element)

// _____________________________________________________________________________

(a) Structure
A B+ Tree is a dynamic hierarchical multi-way data structure consisting
of nodes. Each node stores:

Keys:       Stores integer elements or separator keys.
Children:   Pointers to child nodes.
NumKeys:    Stores the number of keys in the node.
IsLeaf:     Identifies whether the node is a leaf node.
Next:       Pointer to the next leaf node.

The root pointer points to the first node of the B+ Tree.

B+ Tree Property:
- All actual data elements are stored in leaf nodes.
- Internal nodes contain separator keys.
- All leaf nodes are at the same level.
- Leaf nodes are linked from left to right using the next pointer.
- Keys inside every node are maintained in sorted order.

If a node has no child, the corresponding child pointer is NULL.

// _____________________________________________________________________________

(b) Operations

1. Create(bplus)
   Function: Creates an empty B+ Tree.
   Preconditions: None.
   Input: None
   Output: B+ Tree(tree type)
   Postconditions: An empty B+ Tree is created and ROOT is initialized to NULL.

2. Destroy(bplus)
   Function: Deletes the complete B+ Tree and releases all allocated memory.
   Preconditions: B+ Tree should exist.
   Input: B+ Tree (tree type)
   Output: Empty B+ Tree || B+ Tree (tree type)
   Postconditions: All nodes are deleted and the B+ Tree is initialized to an empty tree.

3. InsertElement(bplus, new.element)
   Function: Inserts a new integer element into the existing B+ Tree.
   Preconditions:
   B+ Tree exists.
   B+ Tree may be empty or non-empty.
   Memory should be available.
   The element should be within the valid range.
   Input: B+ Tree (tree type), element (element type)
   Output: B+ Tree (tree type), flag(boolean type)
   Postconditions:
   if flag == 1
   A new element is inserted into the existing B+ Tree
   and the B+ Tree remains balanced.
   else
   Element not inserted.

4. DeleteElement(bplus, delete.element)
   Function: Deletes a specified integer element from the B+ Tree.
   Preconditions:
   B+ Tree exists.
   B+ Tree may be empty or non-empty.
   The element should exist in the B+ Tree.
   Input: B+ Tree (tree type), element (element type)
   Output: B+ Tree (tree type), flag(boolean type)
   Postconditions:
   if flag == 1
   An existing element is deleted from the existing B+ Tree.
   else
   Element not deleted.

5. PrintElement(bplus)
   Function: Prints and displays all elements of the existing B+ Tree using leaf-level traversal.
   Preconditions: B+ Tree is created || B+ Tree should exist.
   Input: B+ Tree (tree type)
   Output: None
   Postconditions: B+ Tree is Print || all elements are visited in sorted order.

6. Search(bplus, search.element)
   Function: Searches for a specified integer element in the B+ Tree.
   Preconditions:
   B+ Tree exists.
   B+ Tree may be empty or non-empty.
   Input: B+ Tree (tree type), element (element type)
   Output: flag(boolean type)
   Postconditions:
   if flag == 1
   Element is found in the B+ Tree.
   else
   Element is not found in the B+ Tree.

// _____________________________________________________________________________
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