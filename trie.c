#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

TrieNode* createTrieNode() {
    TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEnd = 0;
    for (int i = 0; i < ALPHABET; i++)
        node->children[i] = NULL;
    return node;
}

Trie createTrie() {
    return createTrieNode();
}

void insertTrie(Trie root, const char *key) {
    TrieNode *curr = root;
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = tolower(key[i]);
        if (ch < 'a' || ch > 'z') continue;
        int idx = ch - 'a';
        if (curr->children[idx] == NULL)
            curr->children[idx] = createTrieNode();
        curr = curr->children[idx];
    }
    curr->isEnd = 1;
}

int searchTrie(Trie root, const char *key) {
    TrieNode *curr = root;
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = tolower(key[i]);
        if (ch < 'a' || ch > 'z') continue;
        int idx = ch - 'a';
        if (curr->children[idx] == NULL)
            return 0;
        curr = curr->children[idx];
    }
    return curr->isEnd;
}

void destroyTrie(Trie root) {
    if (root == NULL) return;
    for (int i = 0; i < ALPHABET; i++)
        destroyTrie(root->children[i]);
    free(root);
}
/*
=====================================================
PSEUDOCODE FOR TRIE
=====================================================

Algorithm createTrie()
    Create a new TrieNode
    Set isEnd = 0
    Set all children = NULL
    Return the node as root

-----------------------------------------------------

Algorithm insertTrie(root, key)
    curr = root

    For each character ch in key
        Convert ch to lowercase
        idx = ch - 'a'

        If children[idx] is NULL then
            Create a new TrieNode
            Set children[idx] = new node
        End If

        curr = children[idx]
    End For

    Set isEnd of curr = 1

-----------------------------------------------------

Algorithm searchTrie(root, key)
    curr = root

    For each character ch in key
        Convert ch to lowercase
        idx = ch - 'a'

        If children[idx] is NULL then
            Return 0          // not found
        End If

        curr = children[idx]
    End For

    If isEnd of curr is 1 then
        Return 1              // found
    Else
        Return 0
    End If

-----------------------------------------------------

Algorithm destroyTrie(root)
    If root is NULL then Return

    For i = 0 to 25
        destroyTrie(children[i])
    End For

    Free root
=====================================================
*/