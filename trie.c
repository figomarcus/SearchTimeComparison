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