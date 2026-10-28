/* ADT Specifications for B+ Tree of Integers

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



5. TraverseElement(bplus)
Function: Traverses and displays all elements of the existing B+ Tree using leaf-level traversal.
Preconditions: B+ Tree is created || B+ Tree should exist.
Input: B+ Tree (tree type)
Output: None
Postconditions: B+ Tree is traversed || all elements are visited in sorted order.



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

#ifndef BPLUS_H
#define BPLUS_H

#define BPLUS_ORDER 4
#define BPLUS_MAX_KEYS (BPLUS_ORDER - 1)

#define BPLUS_LOWER_BOUND 1
#define BPLUS_UPPER_BOUND 25000


typedef struct BPlusNode
{
    int keys[BPLUS_MAX_KEYS + 1];

    struct BPlusNode *children[BPLUS_ORDER + 1];

    int numKeys;

    int isLeaf;

    struct BPlusNode *next;

} BPlusNode;


typedef struct
{
    BPlusNode *root;

} BPlusTree;


/* Function Declarations */

void createBPlus(BPlusTree *tree);

void destroyBPlus(BPlusTree *tree);

int insertBPlus(BPlusTree *tree, int item);

int deleteBPlus(BPlusTree *tree, int item);

void traverseBPlus(BPlusTree *tree);

int searchBPlus(BPlusTree *tree, int item);

#endif