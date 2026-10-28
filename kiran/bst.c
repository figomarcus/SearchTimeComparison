/*
   File Name: bst.c
   Author: Kiran Gavtalkar
   Roll No: 2605
   Date: 30/09/2026
   Date Modified: 30/09/26
*/

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


/* --------------------------------------------------
   PSEUDOCODE: CREATE
   --------------------------------------------------

   create()
   Step 1: Set root = NULL.
   Step 2: Return root.
*/

/* 1. CREATE */

Node* create()
{
    return NULL;
}


/* --------------------------------------------------
   PSEUDOCODE: INSERT
   --------------------------------------------------

   insert(root, key)

   Step 1: Check whether key is between 1 and 25000.
           If not, display invalid key message
           and return root.

   Step 2: If root is NULL:
              Create a new node.
              Store key in the new node.
              Set left and right to NULL.
              Return the new node.

   Step 3: If key is less than root data:
              Insert key into left subtree.

   Step 4: If key is greater than root data:
              Insert key into right subtree.

   Step 5: Return root.
*/

/* 2. INSERT */

Node* insert(Node *root, int key)
{
    Node *newNode;

    /* Check key range */
    if (key < MIN_KEY || key > MAX_KEY)
    {
        printf("Invalid key! Enter a key between %d and %d.\n",
               MIN_KEY, MAX_KEY);

        return root;
    }

    if (root == NULL)
    {
        newNode = (Node*)malloc(sizeof(Node));

        newNode->data = key;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    if (key < root->data)
    {
        root->left = insert(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = insert(root->right, key);
    }

    return root;
}


/* --------------------------------------------------
   PSEUDOCODE: DELETE
   --------------------------------------------------

   deleteNode(root, key)

   Step 1: Check whether key is between 1 and 25000.
           If not, display invalid key message
           and return root.

   Step 2: If root is NULL:
              Return NULL.

   Step 3: If key is less than root data:
              Delete from left subtree.

   Step 4: If key is greater than root data:
              Delete from right subtree.

   Step 5: If node is found:

              If it has no left child:
                  Store right child in temp.
                  Free current node.
                  Return temp.

              If it has no right child:
                  Store left child in temp.
                  Free current node.
                  Return temp.

              If it has two children:
                  Find smallest node in right subtree.
                  Copy its data.
                  Delete the successor.

   Step 6: Return root.
*/

/* 3. DELETE */

Node* deleteNode(Node *root, int key)
{
    Node *temp;

    /* Check key range */
    if (key < MIN_KEY || key > MAX_KEY)
    {
        printf("Invalid key! Enter a key between %d and %d.\n",
               MIN_KEY, MAX_KEY);

        return root;
    }

    if (root == NULL)
    {
        return NULL;
    }

    if (key < root->data)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = deleteNode(root->right, key);
    }
    else
    {
        /* No child or only right child */

        if (root->left == NULL)
        {
            temp = root->right;

            free(root);

            return temp;
        }

        /* Only left child */

        if (root->right == NULL)
        {
            temp = root->left;

            free(root);

            return temp;
        }

        /* Two children */

        temp = root->right;

        while (temp->left != NULL)
        {
            temp = temp->left;
        }

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}


/* --------------------------------------------------
   PSEUDOCODE: SEARCH
   --------------------------------------------------

   search(root, key)

   Step 1: Check whether key is between 1 and 25000.
           If not, display invalid key message
           and return NULL.

   Step 2: If root is NULL:
              Return NULL.

   Step 3: If key equals root data:
              Return root.

   Step 4: If key is less than root data:
              Search in left subtree.

   Step 5: Otherwise:
              Search in right subtree.
*/

/* 4. SEARCH */

Node* search(Node *root, int key)
{
    /* Check key range */
    if (key < MIN_KEY || key > MAX_KEY)
    {
        printf("Invalid key! Enter a key between %d and %d.\n",
               MIN_KEY, MAX_KEY);

        return NULL;
    }

    if (root == NULL)
    {
        return NULL;
    }

    if (key == root->data)
    {
        return root;
    }

    if (key < root->data)
    {
        return search(root->left, key);
    }

    return search(root->right, key);
}


/* --------------------------------------------------
   PSEUDOCODE: INORDER
   --------------------------------------------------

   inorder(root)

   Step 1: If root is not NULL:
              Traverse left subtree.
              Display root data.
              Traverse right subtree.

   Step 2: Stop.
*/

/* 5. INORDER TRAVERSAL */

void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);

        printf("%d ", root->data);

        inorder(root->right);
    }
}


/* --------------------------------------------------
   PSEUDOCODE: DESTROY
   --------------------------------------------------

   destroy(root)

   Step 1: If root is not NULL:
              Destroy left subtree.
              Destroy right subtree.
              Free current node.

   Step 2: Stop.
*/

/* 6. DESTROY */

void destroy(Node *root)
{
    if (root != NULL)
    {
        destroy(root->left);

        destroy(root->right);

        free(root);
    }
}


/* --------------------------------------------------
   TEST CASES
   --------------------------------------------------

1. CREATE BST

   Expected:
   Empty BST is created.


2. INSERT

   Input:
   50, 30, 70, 20, 40, 60, 80

   Expected BST:

           50
          /  \
        30    70
       / \    / \
     20  40  60 80


3. INORDER TRAVERSAL

   Expected:
   20 30 40 50 60 70 80


4. SEARCH

   Input:
   Search for 40.

   Expected:
   40 found.


5. SEARCH NON-EXISTING KEY

   Input:
   Search for 100.

   Expected:
   100 not found.


6. DELETE LEAF NODE

   Input:
   Delete 20.

   Expected:
   20 is deleted.


7. DELETE NODE WITH ONE CHILD

   Input:
   Delete a node having one child.

   Expected:
   Node is deleted and its child is connected
   to its parent.


8. DELETE NODE WITH TWO CHILDREN

   Input:
   Delete 50.

   Expected:
   Inorder successor replaces 50 and BST property
   is maintained.


9. INORDER TRAVERSAL AGAIN

   Expected:
   Elements are displayed in ascending order.


10. KEY RANGE TEST

   Input:
   Insert 1.
   Insert 25000.
   Insert 0.
   Insert 25001.

   Expected:
   1 and 25000 are accepted.
   0 and 25001 are rejected.


11. DESTROY

   Expected:
   All nodes are deleted and BST becomes empty.

*/