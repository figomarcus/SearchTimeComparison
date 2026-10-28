/*
===============================================================================
 B+ TREE IMPLEMENTATION
 Author: NIDHI NAGVENKAR
 Date: 05-10-2026
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "bplus.h"


// _____________________________________________________________________________


/*
1. Create(bplus)

Function:
    Creates an empty B+ Tree.

Pseudocode:
    1. Check whether tree exists.
    2. Set root to NULL.
    3. Return.
*/


void createBPlus(BPlusTree *tree)
{
    if (tree == NULL)
        return;

    tree->root = NULL;
}


// _____________________________________________________________________________


/*
Helper Function:
    createBPlusNode

Function:
    Creates a new B+ Tree node.

Input:
    isLeaf - 1 if leaf node, 0 if internal node.

Output:
    Pointer to newly created node.
*/


static BPlusNode *createBPlusNode(int isLeaf)
{
    BPlusNode *newNode;
    int i;

    newNode = (BPlusNode *)malloc(sizeof(BPlusNode));

    if (newNode == NULL)
        return NULL;

    newNode->numKeys = 0;
    newNode->isLeaf = isLeaf;
    newNode->next = NULL;

    for (i = 0; i < BPLUS_ORDER + 1; i++)
    {
        newNode->children[i] = NULL;
    }

    return newNode;
}


// _____________________________________________________________________________


/*
2. Destroy(bplus)

Function:
    Deletes the complete B+ Tree and releases all allocated memory.

Pseudocode:
    1. If tree is NULL, return.
    2. Recursively visit all child nodes.
    3. Free every node.
    4. Set root to NULL.
*/


static void destroyBPlusNode(BPlusNode *root)
{
    int i;

    if (root == NULL)
        return;

    if (!root->isLeaf)
    {
        for (i = 0; i <= root->numKeys; i++)
        {
            destroyBPlusNode(root->children[i]);
        }
    }

    free(root);
}


void destroyBPlus(BPlusTree *tree)
{
    if (tree == NULL)
        return;

    destroyBPlusNode(tree->root);

    tree->root = NULL;
}


// _____________________________________________________________________________


/*
Helper Function:
    insertIntoLeaf

Function:
    Inserts an element into a leaf node in sorted order.

Pseudocode:
    1. Start from last key.
    2. Shift larger keys one position right.
    3. Insert new element.
    4. Increase numKeys.
*/


static void insertIntoLeaf(
    BPlusNode *node,
    int item)
{
    int i;

    i = node->numKeys - 1;

    while (i >= 0 && node->keys[i] > item)
    {
        node->keys[i + 1] = node->keys[i];
        i--;
    }

    node->keys[i + 1] = item;

    node->numKeys++;
}


// _____________________________________________________________________________


/*
Helper Function:
    insertIntoInternal

Function:
    Inserts a separator key and child pointer into an internal node.
*/


static void insertIntoInternal(
    BPlusNode *node,
    int key,
    BPlusNode *rightChild)
{
    int i;

    i = node->numKeys - 1;

    while (i >= 0 && node->keys[i] > key)
    {
        node->keys[i + 1] = node->keys[i];

        node->children[i + 2] =
            node->children[i + 1];

        i--;
    }

    node->keys[i + 1] = key;

    node->children[i + 2] = rightChild;

    node->numKeys++;
}


// _____________________________________________________________________________


/*
Helper Function:
    insertBPlusRecursive

Function:
    Recursively inserts an element and handles node splitting.

Output:
    0 -> No split
    1 -> Node split

Pseudocode:
    1. If node is leaf:
         Insert element.
         If overflow occurs, split leaf.
    2. Otherwise:
         Find correct child.
         Recursively insert.
         If child splits, insert promoted key.
    3. If current node overflows, split it.
*/


static int insertBPlusRecursive(
    BPlusNode *node,
    int item,
    int *promotedKey,
    BPlusNode **newChild)
{
    int i;
    int result;


    /*
     * Leaf node.
     */

    if (node->isLeaf)
    {
        insertIntoLeaf(node, item);

        if (node->numKeys <= BPLUS_MAX_KEYS)
            return 0;


        /*
         * Split leaf node.
         */

        {
            BPlusNode *right;
            int splitPoint;
            int j;

            right = createBPlusNode(1);

            if (right == NULL)
                return 0;

            splitPoint = node->numKeys / 2;

            right->numKeys =
                node->numKeys - splitPoint;

            for (j = 0; j < right->numKeys; j++)
            {
                right->keys[j] =
                    node->keys[splitPoint + j];
            }

            node->numKeys = splitPoint;


            /*
             * Link leaf nodes.
             */

            right->next = node->next;

            node->next = right;


            /*
             * First key of right node is
             * promoted to parent.
             */

            *promotedKey = right->keys[0];

            *newChild = right;

            return 1;
        }
    }


    /*
     * Find appropriate child.
     */

    i = 0;

    while (i < node->numKeys &&
           item >= node->keys[i])
    {
        i++;
    }


    result = insertBPlusRecursive(
        node->children[i],
        item,
        promotedKey,
        newChild
    );


    if (!result)
        return 0;


    /*
     * Child was split.
     * Insert promoted key.
     */

    insertIntoInternal(
        node,
        *promotedKey,
        *newChild
    );


    if (node->numKeys <= BPLUS_MAX_KEYS)
        return 0;


    /*
     * Split internal node.
     */

    {
        BPlusNode *right;
        int middle;
        int j;

        right = createBPlusNode(0);

        if (right == NULL)
            return 0;

        middle = node->numKeys / 2;

        *promotedKey = node->keys[middle];

        right->numKeys =
            node->numKeys - middle - 1;


        for (j = 0; j < right->numKeys; j++)
        {
            right->keys[j] =
                node->keys[middle + 1 + j];
        }


        for (j = 0; j <= right->numKeys; j++)
        {
            right->children[j] =
                node->children[middle + 1 + j];
        }


        node->numKeys = middle;


        for (j = middle + 1;
             j < BPLUS_ORDER + 1;
             j++)
        {
            node->children[j] = NULL;
        }


        *newChild = right;

        return 1;
    }
}


// _____________________________________________________________________________


/*
3. InsertElement(bplus, new.element)

Function:
    Inserts a new integer element into the B+ Tree.

Pseudocode:
    1. Check tree and element.
    2. If tree is empty:
         Create a leaf root.
         Insert element.
    3. Otherwise recursively insert element.
    4. If root splits:
         Create a new root.
    5. Return flag.
*/


int insertBPlus(BPlusTree *tree, int item)
{
    int promotedKey;
    BPlusNode *newChild;


    if (tree == NULL)
        return 0;


    if (item < BPLUS_LOWER_BOUND ||
        item > BPLUS_UPPER_BOUND)
    {
        return 0;
    }


    /*
     * Empty tree.
     */

    if (tree->root == NULL)
    {
        tree->root = createBPlusNode(1);

        if (tree->root == NULL)
            return 0;

        tree->root->keys[0] = item;

        tree->root->numKeys = 1;

        return 1;
    }


    /*
     * Insert into existing tree.
     */

    if (insertBPlusRecursive(
            tree->root,
            item,
            &promotedKey,
            &newChild))
    {
        BPlusNode *newRoot;

        newRoot = createBPlusNode(0);

        if (newRoot == NULL)
            return 0;

        newRoot->keys[0] = promotedKey;

        newRoot->numKeys = 1;

        newRoot->children[0] = tree->root;

        newRoot->children[1] = newChild;

        tree->root = newRoot;
    }

    return 1;
}


// _____________________________________________________________________________


/*
Helper Function:
    findBPlusLeaf

Function:
    Finds the leaf node where an element should exist.

Pseudocode:
    1. If current node is leaf, return it.
    2. Compare element with separator keys.
    3. Move to appropriate child.
    4. Repeat until leaf is reached.
*/


static BPlusNode *findBPlusLeaf(
    BPlusNode *root,
    int item)
{
    int i;

    if (root == NULL)
        return NULL;

    if (root->isLeaf)
        return root;


    i = 0;

    while (i < root->numKeys &&
           item >= root->keys[i])
    {
        i++;
    }


    return findBPlusLeaf(
        root->children[i],
        item
    );
}


// _____________________________________________________________________________


/*
6. Search(bplus, search.element)

Function:
    Searches for a specified element in the B+ Tree.

Pseudocode:
    1. Start from root.
    2. Follow separator keys.
    3. Reach appropriate leaf.
    4. Search keys in leaf.
    5. Return flag.
*/


int searchBPlus(
    BPlusTree *tree,
    int item)
{
    BPlusNode *leaf;
    int i;


    if (tree == NULL ||
        tree->root == NULL)
    {
        return 0;
    }


    leaf = findBPlusLeaf(
        tree->root,
        item
    );


    if (leaf == NULL)
        return 0;


    for (i = 0; i < leaf->numKeys; i++)
    {
        if (leaf->keys[i] == item)
            return 1;
    }


    return 0;
}


// _____________________________________________________________________________


/*
Helper Function:
    getFirstKey

Function:
    Gets the smallest key in a subtree.
*/


static int getFirstKey(BPlusNode *node)
{
    if (node == NULL)
        return -1;


    while (!node->isLeaf)
    {
        node = node->children[0];
    }


    if (node->numKeys == 0)
        return -1;


    return node->keys[0];
}


// _____________________________________________________________________________


/*
Helper Function:
    updateSeparators

Function:
    Updates separator keys after deletion.
*/


static void updateSeparators(BPlusNode *node)
{
    int i;


    if (node == NULL ||
        node->isLeaf)
    {
        return;
    }


    for (i = 0; i < node->numKeys; i++)
    {
        node->keys[i] =
            getFirstKey(
                node->children[i + 1]
            );
    }


    for (i = 0; i <= node->numKeys; i++)
    {
        updateSeparators(
            node->children[i]
        );
    }
}


// _____________________________________________________________________________


/*
4. DeleteElement(bplus, delete.element)

Function:
    Deletes a specified integer element from the B+ Tree.

Pseudocode:
    1. Find the leaf containing the element.
    2. If element does not exist, return 0.
    3. Shift elements to remove the element.
    4. Decrease numKeys.
    5. Update separator keys.
    6. Return flag.
*/


int deleteBPlus(
    BPlusTree *tree,
    int item)
{
    BPlusNode *leaf;
    int i;
    int position = -1;


    if (tree == NULL ||
        tree->root == NULL)
    {
        return 0;
    }


    leaf = findBPlusLeaf(
        tree->root,
        item
    );


    if (leaf == NULL)
        return 0;


    /*
     * Find element.
     */

    for (i = 0; i < leaf->numKeys; i++)
    {
        if (leaf->keys[i] == item)
        {
            position = i;
            break;
        }
    }


    if (position == -1)
        return 0;


    /*
     * Delete element.
     */

    for (i = position;
         i < leaf->numKeys - 1;
         i++)
    {
        leaf->keys[i] =
            leaf->keys[i + 1];
    }


    leaf->numKeys--;


    /*
     * Empty root.
     */

    if (tree->root->isLeaf &&
        tree->root->numKeys == 0)
    {
        free(tree->root);

        tree->root = NULL;

        return 1;
    }


    /*
     * Update separator keys.
     */

    updateSeparators(tree->root);


    return 1;
}


// _____________________________________________________________________________


/*
Helper Function:
    getFirstLeaf

Function:
    Finds the leftmost leaf node.
*/


static BPlusNode *getFirstLeaf(
    BPlusNode *root)
{
    if (root == NULL)
        return NULL;


    while (!root->isLeaf)
    {
        root = root->children[0];
    }


    return root;
}


// _____________________________________________________________________________


/*
5. TraverseElement(bplus)

Function:
    Traverses and displays all elements using leaf-level traversal.

Pseudocode:
    1. Find the first leaf node.
    2. Display all keys in the leaf.
    3. Move to next leaf using next pointer.
    4. Repeat until next is NULL.
*/


void traverseBPlus(
    BPlusTree *tree)
{
    BPlusNode *current;
    int i;


    if (tree == NULL ||
        tree->root == NULL)
    {
        printf("B+ Tree is empty.\n");
        return;
    }


    current = getFirstLeaf(
        tree->root
    );


    printf("B+ Tree Elements: ");


    while (current != NULL)
    {
        for (i = 0;
             i < current->numKeys;
             i++)
        {
            printf("%d ",
                   current->keys[i]);
        }


        current = current->next;
    }


    printf("\n");
}


// _____________________________________________________________________________


/*
TEST CASES

1. Create an empty B+ Tree.
   Expected Output:
       Root is initialized to NULL.

2. Insert:
       10, 20, 5, 30, 15
   Expected Output:
       All elements are inserted.

3. Search:
       20
   Expected Output:
       Element found.

4. Search:
       100
   Expected Output:
       Element not found.

5. Delete:
       20
   Expected Output:
       Element deleted.

6. Delete:
       100
   Expected Output:
       Element not deleted.

7. Traverse:
       Expected Output:
       Elements displayed in sorted order.

8. Destroy:
       Expected Output:
       All nodes are deleted.
*/