/*
   File Name: btree.h
   Author: Kiran Gavtalkar
   Roll No: 2605
   Date: 28/09/2026
   Date Modified: 30/09/26
*/

/* 
   ADT Specification – B-TREE
   
ADT Name: B-Tree

a):Structure
A B-Tree is a balanced multi-way search tree.
A node can contain multiple keys and multiple children.

The keys in each node are stored in sorted order.
All leaf nodes are at the same level.

Key Range:
Minimum key = 1
Maximum key = 25000.


b)Operations:

Create (create())
Insert (insert())
Search (search())
Delete (deleteKey())
Traverse (traverse())
Destroy (destroy())

////////////////////////////////////////
1. Function: create()
Purpose:Creates an empty B-Tree.
Precondition:None.
Input:None.
Output:Btree(Btree type)
Postcondition:A new empty B-Tree is created and the root is NULL.


2. Function: insert()
Purpose:Inserts a new key into the B-Tree while maintaining
the B-Tree properties.
Precondition:B-Tree must exist.
Input:BTree (Btree type), key(int).
Key Range: 1 to 25000.
Output:Btree(Btree type)
Postcondition:The key is inserted in the correct position and
the B-Tree remains balanced.


3. Function: search()
Purpose:Searches for a specified key in the B-Tree.
Precondition:B-Tree must exist.
Input:Btree (Btree type), key(int).
Output:The node containing the key if found,otherwise NULL.
Postcondition:The B-Tree remains unchanged.


4. Function: deleteKey()
Purpose:Deletes a specified key from the BTree.
Precondition:BTree must exist.
Input:BTree (btree), key(int).
Output:Updated BTree.
Postcondition:The key is removed and the BTree properties
are maintained.


5. Function: traverse()
Purpose:Visits and displays all keys of the B-Tree in sorted order.
Precondition:B-Tree must exist.
Input:BTree(btree type)
Output:Keys of the B-Tree in ascending order.
Postcondition:All keys are displayed in sorted order.


6. Function: destroy()
Purpose:Deletes the entire B-Tree and releases memory.
Precondition:BTree must exist.
Input:BTree(btree type)
Output:btree(null)
Postcondition:All nodes of the B-Tree are deleted and the tree
becomes empty.


--------------------------------------------------
structure and FUNCTION DECLARATIONS
-------------------------------------------------- */

#define T 3
#define MIN_KEY 1
#define MAX_KEY 25000

typedef struct BTreeNode
{
    int keys[2 * T - 1];
    struct BTreeNode *children[2 * T];
    int n;
    int leaf;
} BTreeNode;

BTreeNode* create();

void insert(BTreeNode **root, int key);

BTreeNode* search(BTreeNode *root, int key);

void deleteKey(BTreeNode **root, int key);

void traverse(BTreeNode *root);

void destroy(BTreeNode *root);