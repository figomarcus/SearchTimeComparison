/* ADT Specifications for B* Tree of Integers

(a) Structure:
A B* Tree is a dynamic multi-way search tree in which each node
can contain multiple keys and multiple child pointers. The tree
remains balanced by splitting nodes when required.

For every B* Tree:
    - The tree is a multi-way search tree.
    - Keys inside every node are maintained in sorted order.
    - Internal nodes contain separator keys.
    - Leaf nodes contain actual data elements.
    - All paths from the root to the leaf nodes are maintained
      at the same level.
    - ORDER represents the maximum number of children.
    - Maximum number of keys in a node is ORDER - 1.

For this implementation:
    ORDER = 4
    Maximum children = 4
    Maximum keys = 3

(b) Operations:
    (i)   Create(bstar)
    (ii)  Destroy(bstar)
    (iii) InsertElement(bstar, new.element)
    (iv)  DeleteElement(bstar, delete.element)
    (v)   TraverseElement(bstar)
    (vi)  Search(bstar, search.element)



// _____________________________________________________________________________


(a) Structure
A B* Tree is a dynamic hierarchical multi-way data structure consisting
of nodes. Each node stores:

Keys:       Stores integer elements or separator keys.
Children:   Pointers to child nodes.
NumKeys:    Stores the number of keys in the node.
IsLeaf:     Identifies whether the node is a leaf node.

The root pointer points to the first node of the B* Tree.

B* Tree Property:
    - Each node can contain multiple keys.
    - Internal nodes contain separator keys.
    - Leaf nodes contain data elements.
    - Keys inside every node are maintained in sorted order.
    - The tree remains balanced after insertion.
    - When a node becomes full, it is split and the middle key
      is promoted to the parent.

If a node has no child, the corresponding child pointer is NULL.


// _____________________________________________________________________________


(b) Operations

1. Create(bstar)
Function: Creates an empty B* Tree.
Preconditions: None.
Input: None
Output: B* Tree(tree type)
Postconditions: An empty B* Tree is created and ROOT is initialized to NULL.


2. Destroy(bstar)
Function: Deletes the complete B* Tree and releases
          all allocated memory.
Preconditions: B* Tree should exist.
Input: B* Tree (tree type)
Output: Empty B* Tree || B* Tree (tree type)
Postconditions: All nodes are deleted and the B* Tree is initialized
                to an empty tree.



3. InsertElement(bstar, new.element)
Function: Inserts a new integer element into the existing B* Tree.
Preconditions:
    B* Tree exists.
    B* Tree may be empty or non-empty.
    Memory should be available.
    The element should be within the valid range.
Input: B* Tree (tree type), element (element type)
Output: B* Tree (tree type), flag(boolean type)
Postconditions:
    if flag == 1
       A new element is inserted into the existing B* Tree
       and the B* Tree remains balanced.
    else
       Element not inserted.



4. DeleteElement(bstar, delete.element)
Function: Deletes a specified integer element from the B* Tree.
Preconditions:
    B* Tree exists.
    B* Tree may be empty or non-empty.
    The element should exist in the B* Tree.
Input: B* Tree (tree type), element (element type)
Output: B* Tree (tree type), flag(boolean type)
Postconditions:
    if flag == 1
       An existing element is deleted from the existing B* Tree.
    else
       Element not deleted.



5. TraverseElement(bstar)
Function: Traverses and displays all elements of the existing B* Tree
          using inorder traversal.
Preconditions: B* Tree is created || B* Tree should exist.
Input: B* Tree (tree type)
Output: None
Postconditions: B* Tree is traversed || all elements are visited
                in sorted order.



6. Search(bstar, search.element)
Function: Searches for a specified integer element in the B* Tree.
Preconditions:
    B* Tree exists.
    B* Tree may be empty or non-empty.
Input: B* Tree (tree type), element (element type)
Output: flag(boolean type)
Postconditions:
    if flag == 1
       Element is found in the B* Tree.
    else
       Element is not found in the B* Tree.



// _____________________________________________________________________________
*/

#ifndef BSTAR_H
#define BSTAR_H

#define BSTAR_ORDER 4
#define BSTAR_MAX_KEYS (BSTAR_ORDER - 1)

#define BSTAR_LOWER_BOUND 1
#define BSTAR_UPPER_BOUND 25000


typedef struct BStarNode
{
    int keys[BSTAR_MAX_KEYS + 1];

    struct BStarNode *children[BSTAR_ORDER + 1];

    int numKeys;

    int isLeaf;

} BStarNode;


typedef struct
{
    BStarNode *root;

} BStarTree;


/* Function Declarations */

void createBStar(BStarTree *tree);

void destroyBStar(BStarTree *tree);

int insertBStar(BStarTree *tree, int item);

int deleteBStar(BStarTree *tree, int item);

void traverseBStar(BStarTree *tree);

int searchBStar(BStarTree *tree, int item);

#endif