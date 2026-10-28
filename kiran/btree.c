/*
   File Name: btree.c
   Author: Kiran Gavtalkar
   Roll No: 2605
   Date: 30/09/2026
*/

#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

/* --------------------------------------------------
   PSEUDOCODE: CREATE
   --------------------------------------------------

   create()

   Step 1: Set root = NULL.
   Step 2: Return root.
*/

/* 1. CREATE */

BTreeNode* create()
{
    return NULL;
}

/* --------------------------------------------------
   CREATE NEW NODE
   -------------------------------------------------- */

BTreeNode* createNode(int leaf)
{
    BTreeNode *node;
    int i;

    node = (BTreeNode*)malloc(sizeof(BTreeNode));

    node->n = 0;
    node->leaf = leaf;

    for (i = 0; i < 2 * T; i++)
    {
        node->children[i] = NULL;
    }

    return node;
}

/* --------------------------------------------------
   PSEUDOCODE: TRAVERSE
   --------------------------------------------------

   traverse(root)

   Step 1: If root is NULL, return.
   Step 2: For every key:
              Traverse the child before the key.
              Display the key.
   Step 3: Traverse the last child.
*/

/* 2. TRAVERSE */

void traverse(BTreeNode *root)
{
    int i;

    if (root == NULL)
    {
        return;
    }

    for (i = 0; i < root->n; i++)
    {
        if (root->leaf == 0)
        {
            traverse(root->children[i]);
        }

        printf("%d ", root->keys[i]);
    }

    if (root->leaf == 0)
    {
        traverse(root->children[root->n]);
    }
}

/* --------------------------------------------------
   PSEUDOCODE: SEARCH
   --------------------------------------------------

   search(root, key)

   Step 1: Start from the first key.
   Step 2: Find the first key greater than or equal
           to the search key.
   Step 3: If the key is found, return the node.
   Step 4: If the node is a leaf, return NULL.
   Step 5: Otherwise search the correct child.
*/

/* 3. SEARCH */

BTreeNode* search(BTreeNode *root, int key)
{
    int i;

    if (root == NULL)
    {
        return NULL;
    }

    i = 0;

    while (i < root->n && key > root->keys[i])
    {
        i++;
    }

    if (i < root->n && key == root->keys[i])
    {
        return root;
    }

    if (root->leaf == 1)
    {
        return NULL;
    }

    return search(root->children[i], key);
}

/* --------------------------------------------------
   SPLIT CHILD
   -------------------------------------------------- */

void splitChild(BTreeNode *parent, int index)
{
    BTreeNode *oldNode;
    BTreeNode *newNode;
    int i;

    oldNode = parent->children[index];

    newNode = createNode(oldNode->leaf);

    newNode->n = T - 1;

    for (i = 0; i < T - 1; i++)
    {
        newNode->keys[i] = oldNode->keys[i + T];
    }

    if (oldNode->leaf == 0)
    {
        for (i = 0; i < T; i++)
        {
            newNode->children[i] =
                oldNode->children[i + T];
        }
    }

    oldNode->n = T - 1;

    for (i = parent->n; i >= index + 1; i--)
    {
        parent->children[i + 1] =
            parent->children[i];
    }

    parent->children[index + 1] = newNode;

    for (i = parent->n - 1; i >= index; i--)
    {
        parent->keys[i + 1] =
            parent->keys[i];
    }

    parent->keys[index] =
        oldNode->keys[T - 1];

    parent->n++;
}

/* --------------------------------------------------
   INSERT INTO NON-FULL NODE
   -------------------------------------------------- */

void insertNonFull(BTreeNode *node, int key)
{
    int i;

    i = node->n - 1;

    if (node->leaf == 1)
    {
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] =
                node->keys[i];

            i--;
        }

        node->keys[i + 1] = key;

        node->n++;
    }
    else
    {
        while (i >= 0 && key < node->keys[i])
        {
            i--;
        }

        i++;

        if (node->children[i]->n == 2 * T - 1)
        {
            splitChild(node, i);

            if (key > node->keys[i])
            {
                i++;
            }
        }

        insertNonFull(node->children[i], key);
    }
}

/* --------------------------------------------------
   PSEUDOCODE: INSERT
   --------------------------------------------------

   insert(root, key)

   Step 1: Check whether key is between 1 and 25000.
   Step 2: If root is NULL:
              Create a new root.
              Insert key.
   Step 3: If root is full:
              Create a new root.
              Split the old root.
              Insert key into the correct child.
   Step 4: Otherwise insert key into the non-full root.
*/

/* 4. INSERT */

void insert(BTreeNode **root, int key)
{
    BTreeNode *newRoot;

    if (key < MIN_KEY || key > MAX_KEY)
    {
        printf("Invalid key! Enter a key between %d and %d.\n",
               MIN_KEY, MAX_KEY);
        return;
    }

    if (*root == NULL)
    {
        *root = createNode(1);

        (*root)->keys[0] = key;
        (*root)->n = 1;

        return;
    }

    if ((*root)->n == 2 * T - 1)
    {
        newRoot = createNode(0);

        newRoot->children[0] = *root;

        splitChild(newRoot, 0);

        if (key > newRoot->keys[0])
        {
            insertNonFull(newRoot->children[1], key);
        }
        else
        {
            insertNonFull(newRoot->children[0], key);
        }

        *root = newRoot;
    }
    else
    {
        insertNonFull(*root, key);
    }
}

/* --------------------------------------------------
   PSEUDOCODE: DELETE
   --------------------------------------------------

   deleteKey(root, key)

   Step 1: Check whether key is between 1 and 25000.
   Step 2: Search for the key.
   Step 3: Delete the key from the B-Tree.
   Step 4: Maintain the B-Tree properties.

   Note:
   This implementation provides a simple deletion
   for keys stored in leaf nodes.
*/

/* 5. DELETE */

void deleteKey(BTreeNode **root, int key)
{
    BTreeNode *node;
    int i;

    if (key < MIN_KEY || key > MAX_KEY)
    {
        printf("Invalid key! Enter a key between %d and %d.\n",
               MIN_KEY, MAX_KEY);
        return;
    }

    node = search(*root, key);

    if (node == NULL)
    {
        return;
    }

    if (node->leaf == 0)
    {
        printf("Deletion of internal key is not implemented.\n");
        return;
    }

    i = 0;

    while (i < node->n && node->keys[i] != key)
    {
        i++;
    }

    while (i < node->n - 1)
    {
        node->keys[i] = node->keys[i + 1];
        i++;
    }

    node->n--;

    if (node->n == 0 && node == *root)
    {
        free(node);
        *root = NULL;
    }
}

/* --------------------------------------------------
   PSEUDOCODE: DESTROY
   --------------------------------------------------

   destroy(root)

   Step 1: If root is NULL, return.
   Step 2: If root is not a leaf:
              Destroy all children.
   Step 3: Free the current node.
*/

/* 6. DESTROY */

void destroy(BTreeNode *root)
{
    int i;

    if (root == NULL)
    {
        return;
    }

    if (root->leaf == 0)
    {
        for (i = 0; i <= root->n; i++)
        {
            destroy(root->children[i]);
        }
    }

    free(root);
}

/* --------------------------------------------------
   TEST CASES
   --------------------------------------------------

1. CREATE

   Expected:
   Empty B-Tree.


2. INSERT

   Input:
   10, 20, 5, 6, 12, 30, 7, 17

   Expected:
   Keys are inserted while maintaining the
   B-Tree properties.


3. TRAVERSE

   Expected:
   5 6 7 10 12 17 20 30


4. SEARCH

   Input:
   Search for 12.

   Expected:
   12 found.


5. SEARCH NON-EXISTING KEY

   Input:
   Search for 100.

   Expected:
   100 not found.


6. DELETE

   Input:
   Delete 7.

   Expected:
   7 is deleted.


7. TRAVERSE AGAIN

   Expected:
   Keys are displayed in ascending order.


8. DESTROY

   Expected:
   All B-Tree nodes are deleted.

*/