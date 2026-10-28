/*
   Author: Kiran Gavtalkar
   Roll No: 2605
   Date: 30/09/2026
   date modified:3/09/2026
*/

/* --------------------------------------------------
   ADT Specification – BST of integers

ADT Name: Binary Search Tree (BST)

a):Structure
A Binary Search Tree is a binary tree in which the
elements smaller than the root are stored in the left
subtree and the elements greater than the root are
stored in the right subtree.

Each node contains a data value, a pointer to the
left child and a pointer to the right child.

Key Range:
Minimum key = 1
Maximum key = 25000.

b)Operations:

Create (create())
Insert (insert())
Delete Node (deleteNode())
Search (search())
Inorder Traverse (inorder())
Destroy (destroy())

///////////////////////////////////
1. Function: create()
Purpose:Creates an empty Binary Search Tree.
Precondition:None.
Input:None.
Output:BST(tree type)
Postcondition:A new empty BST is created and the root is NULL.


2. Function: insert()
Purpose:Inserts a new element into the Binary Search Tree.
Precondition:BST must exist.
Input:BST(tree type)
Output:Updated BST.
Key Range: 1 to 25000.
Postcondition:The new element is inserted in the correct position
according to the BST property.


3. Function: deleteNode()
Purpose:Deletes a specified node from the Binary Search Tree.
Precondition:BST must exist.
Input:BST (tree type)
Output:Updated BST.
Postcondition:The specified node is removed while maintaining
the BST property.


4. Function: search()
Purpose:Searches for a specified element in the Binary Search Tree.
Precondition:BST must exist.
Input:BST (tree type),key(int).
Output:The node containing the element if found,otherwise NULL.
Postcondition:The BST remains unchanged.

5. Function: inorder()
Purpose:Visits and displays all nodes of the BST in inorder.
Precondition:BST must exist.
Input:BST(tree type)
Output:Elements of the BST in ascending order.
Postcondition:All nodes are visited in the order:
Left → Root → Right


6. Function: destroy()
Purpose:Deletes the entire BST and releases allocated memory.
Precondition:BST must exist.
Input:BST(tree type)
Output:BST(null)
Postcondition:All nodes of the BST are deleted and the tree
becomes empty.


/* --------------------------------------------------
   structure and function declarations
   -------------------------------------------------- */

#define MIN_KEY 1
#define MAX_KEY 25000

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;


Node* create();

Node* insert(Node *root, int key);

Node* deleteNode(Node *root, int key);

Node* search(Node *root, int key);

void inorder(Node *root);

void destroy(Node *root);