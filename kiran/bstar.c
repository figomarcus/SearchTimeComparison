/*
===============================================================================
 B* TREE IMPLEMENTATION
 Author: NIDHI NAGVENKAR
 Date: 05-10-2026
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "bstar.h"


// _____________________________________________________________________________


/*
1. Create(bstar)

Function:
    Creates an empty B* Tree.

Pseudocode:
    1. Check whether tree exists.
    2. Set root to NULL.
    3. Return.
*/


void createBStar(BStarTree *tree)
{
    if (tree == NULL)
        return;

    tree->root = NULL;
}


// _____________________________________________________________________________


/*
Helper Function:
    createBStarNode

Function:
    Creates a new B* Tree node.

Input:
    isLeaf - 1 if leaf node, 0 if internal node.

Output:
    Pointer to newly created node.
*/


static BStarNode *createBStarNode(
    int isLeaf)
{
    BStarNode *newNode;
    int i;


    newNode =
        (BStarNode *)malloc(
            sizeof(BStarNode)
        );


    if (newNode == NULL)
        return NULL;


    newNode->numKeys = 0;

    newNode->isLeaf = isLeaf;


    for (i = 0;
         i < BSTAR_ORDER + 1;
         i++)
    {
        newNode->children[i] = NULL;
    }


    return newNode;
}


// _____________________________________________________________________________


/*
2. Destroy(bstar)

Function:
    Deletes the complete B* Tree and releases all allocated memory.

Pseudocode:
    1. If tree is NULL, return.
    2. Recursively visit all child nodes.
    3. Free every node.
    4. Set root to NULL.
*/


static void destroyBStarNode(
    BStarNode *root)
{
    int i;


    if (root == NULL)
        return;


    if (!root->isLeaf)
    {
        for (i = 0;
             i <= root->numKeys;
             i++)
        {
            destroyBStarNode(
                root->children[i]
            );
        }
    }


    free(root);
}


void destroyBStar(
    BStarTree *tree)
{
    if (tree == NULL)
        return;


    destroyBStarNode(
        tree->root
    );


    tree->root = NULL;
}


// _____________________________________________________________________________


/*
Helper Function:
    insertIntoNode

Function:
    Inserts a key into a node in sorted order.
*/


static void insertIntoNode(
    BStarNode *node,
    int item,
    BStarNode *rightChild)
{
    int i;


    i = node->numKeys - 1;


    while (i >= 0 &&
           node->keys[i] > item)
    {
        node->keys[i + 1] =
            node->keys[i];


        if (!node->isLeaf)
        {
            node->children[i + 2] =
                node->children[i + 1];
        }


        i--;
    }


    node->keys[i + 1] = item;


    if (!node->isLeaf)
    {
        node->children[i + 2] =
            rightChild;
    }


    node->numKeys++;
}


// _____________________________________________________________________________


/*
Helper Function:
    insertBStarRecursive

Function:
    Recursively inserts an element and handles node splitting.

Pseudocode:
    1. If leaf:
         Insert element.
         Check overflow.
    2. If overflow:
         Split node.
         Promote middle key.
    3. If internal:
         Find appropriate child.
         Recursively insert.
    4. If child splits:
         Insert promoted key.
    5. If current node overflows:
         Split current node.
*/


static int insertBStarRecursive(
    BStarNode *node,
    int item,
    int *promotedKey,
    BStarNode **newChild)
{
    int i;
    int result;


    /*
     * Leaf node.
     */

    if (node->isLeaf)
    {
        i = node->numKeys - 1;


        while (i >= 0 &&
               node->keys[i] > item)
        {
            node->keys[i + 1] =
                node->keys[i];

            i--;
        }


        node->keys[i + 1] = item;

        node->numKeys++;


        /*
         * No overflow.
         */

        if (node->numKeys <= BSTAR_MAX_KEYS)
            return 0;


        /*
         * Split leaf.
         */

        {
            BStarNode *right;
            int middle;
            int j;


            right =
                createBStarNode(1);


            if (right == NULL)
                return 0;


            middle =
                node->numKeys / 2;


            *promotedKey =
                node->keys[middle];


            right->numKeys =
                node->numKeys -
                middle - 1;


            for (j = 0;
                 j < right->numKeys;
                 j++)
            {
                right->keys[j] =
                    node->keys[
                        middle + 1 + j
                    ];
            }


            node->numKeys = middle;


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


    result =
        insertBStarRecursive(
            node->children[i],
            item,
            promotedKey,
            newChild
        );


    if (!result)
        return 0;


    /*
     * Child has split.
     */

    insertIntoNode(
        node,
        *promotedKey,
        *newChild
    );


    /*
     * No overflow.
     */

    if (node->numKeys <= BSTAR_MAX_KEYS)
        return 0;


    /*
     * Split internal node.
     */

    {
        BStarNode *right;
        int middle;
        int j;


        right =
            createBStarNode(0);


        if (right == NULL)
            return 0;


        middle =
            node->numKeys / 2;


        *promotedKey =
            node->keys[middle];


        right->numKeys =
            node->numKeys -
            middle - 1;


        for (j = 0;
             j < right->numKeys;
             j++)
        {
            right->keys[j] =
                node->keys[
                    middle + 1 + j
                ];
        }


        for (j = 0;
             j <= right->numKeys;
             j++)
        {
            right->children[j] =
                node->children[
                    middle + 1 + j
                ];
        }


        node->numKeys = middle;


        for (j = middle + 1;
             j < BSTAR_ORDER + 1;
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
3. InsertElement(bstar, new.element)

Function:
    Inserts a new integer element into the B* Tree.

Pseudocode:
    1. Check tree and element.
    2. If tree is empty:
         Create root.
         Insert element.
    3. Otherwise recursively insert element.
    4. If root splits:
         Create new root.
    5. Return flag.
*/


int insertBStar(
    BStarTree *tree,
    int item)
{
    int promotedKey;
    BStarNode *newChild;


    if (tree == NULL)
        return 0;


    if (item < BSTAR_LOWER_BOUND ||
        item > BSTAR_UPPER_BOUND)
    {
        return 0;
    }


    /*
     * Empty tree.
     */

    if (tree->root == NULL)
    {
        tree->root =
            createBStarNode(1);


        if (tree->root == NULL)
            return 0;


        tree->root->keys[0] =
            item;


        tree->root->numKeys = 1;


        return 1;
    }


    /*
     * Insert into existing tree.
     */

    if (insertBStarRecursive(
            tree->root,
            item,
            &promotedKey,
            &newChild))
    {
        BStarNode *newRoot;


        newRoot =
            createBStarNode(0);


        if (newRoot == NULL)
            return 0;


        newRoot->keys[0] =
            promotedKey;


        newRoot->numKeys = 1;


        newRoot->children[0] =
            tree->root;


        newRoot->children[1] =
            newChild;


        tree->root = newRoot;
    }


    return 1;
}


// _____________________________________________________________________________


/*
Helper Function:
    searchBStarNode

Function:
    Searches for an element recursively.

Pseudocode:
    1. Start from current node.
    2. Compare element with keys.
    3. If found, return 1.
    4. If leaf, return 0.
    5. Otherwise move to appropriate child.
*/


static int searchBStarNode(
    BStarNode *node,
    int item)
{
    int i;


    if (node == NULL)
        return 0;


    i = 0;


    while (i < node->numKeys &&
           item > node->keys[i])
    {
        i++;
    }


    if (i < node->numKeys &&
        item == node->keys[i])
    {
        return 1;
    }


    if (node->isLeaf)
        return 0;


    return searchBStarNode(
        node->children[i],
        item
    );
}


// _____________________________________________________________________________


/*
6. Search(bstar, search.element)

Function:
    Searches for a specified element in the B* Tree.

Pseudocode:
    1. Check whether tree exists.
    2. Start searching from root.
    3. Compare keys.
    4. Move to appropriate child.
    5. Return flag.
*/


int searchBStar(
    BStarTree *tree,
    int item)
{
    if (tree == NULL ||
        tree->root == NULL)
    {
        return 0;
    }


    return searchBStarNode(
        tree->root,
        item
    );
}


// _____________________________________________________________________________


/*
Helper Function:
    getPredecessor

Function:
    Finds the largest element in a subtree.
*/


static int getPredecessor(
    BStarNode *node)
{
    while (!node->isLeaf)
    {
        node =
            node->children[
                node->numKeys
            ];
    }


    return node->keys[
        node->numKeys - 1
    ];
}


// _____________________________________________________________________________


/*
Helper Function:
    deleteBStarRecursive

Function:
    Deletes an element recursively.

Pseudocode:
    1. Search for the element.
    2. If leaf:
         Remove the element.
    3. If internal:
         Find predecessor.
         Replace current key with predecessor.
         Delete predecessor recursively.
    4. Return flag.
*/


static int deleteBStarRecursive(
    BStarNode *node,
    int item)
{
    int i;
    int j;


    i = 0;


    while (i < node->numKeys &&
           item > node->keys[i])
    {
        i++;
    }


    /*
     * Element found.
     */

    if (i < node->numKeys &&
        item == node->keys[i])
    {
        /*
         * Leaf node.
         */

        if (node->isLeaf)
        {
            for (j = i;
                 j < node->numKeys - 1;
                 j++)
            {
                node->keys[j] =
                    node->keys[j + 1];
            }


            node->numKeys--;


            return 1;
        }


        /*
         * Internal node.
         *
         * Replace with predecessor.
         */

        {
            int predecessor;


            predecessor =
                getPredecessor(
                    node->children[i]
                );


            node->keys[i] =
                predecessor;


            return deleteBStarRecursive(
                node->children[i],
                predecessor
            );
        }
    }


    /*
     * Element not found.
     */

    if (node->isLeaf)
        return 0;


    return deleteBStarRecursive(
        node->children[i],
        item
    );
}


// _____________________________________________________________________________


/*
4. DeleteElement(bstar, delete.element)

Function:
    Deletes a specified integer element from the B* Tree.

Pseudocode:
    1. Check tree.
    2. Search for element.
    3. If element is not found, return 0.
    4. Delete element recursively.
    5. If root becomes empty:
         Adjust root.
    6. Return flag.
*/


int deleteBStar(
    BStarTree *tree,
    int item)
{
    int result;
    BStarNode *oldRoot;


    if (tree == NULL ||
        tree->root == NULL)
    {
        return 0;
    }


    result =
        deleteBStarRecursive(
            tree->root,
            item
        );


    if (result)
    {
        /*
         * Root becomes empty.
         */

        if (tree->root->numKeys == 0)
        {
            oldRoot = tree->root;


            if (tree->root->isLeaf)
            {
                tree->root = NULL;
            }
            else
            {
                tree->root =
                    tree->root->children[0];
            }


            free(oldRoot);
        }
    }


    return result;
}


// _____________________________________________________________________________


/*
5. TraverseElement(bstar)

Function:
    Traverses and displays all elements of the B* Tree using
    inorder traversal.

Pseudocode:
    1. Visit left child.
    2. Display key.
    3. Visit next child.
    4. Continue until all nodes are visited.
*/


static void traverseBStarNode(
    BStarNode *node)
{
    int i;


    if (node == NULL)
        return;


    for (i = 0;
         i < node->numKeys;
         i++)
    {
        if (!node->isLeaf)
        {
            traverseBStarNode(
                node->children[i]
            );
        }


        printf("%d ",
               node->keys[i]);
    }


    if (!node->isLeaf)
    {
        traverseBStarNode(
            node->children[
                node->numKeys
            ]
        );
    }
}


void traverseBStar(
    BStarTree *tree)
{
    if (tree == NULL ||
        tree->root == NULL)
    {
        printf("B* Tree is empty.\n");
        return;
    }


    printf("B* Tree Elements: ");


    traverseBStarNode(
        tree->root
    );


    printf("\n");
}


// _____________________________________________________________________________


/*
TEST CASES

1. Create an empty B* Tree.
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