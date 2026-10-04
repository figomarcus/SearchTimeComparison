/*
    Name        : [Figo Marcus Fernandes]
    Class       : [MSc AI]
    Roll Number : [2604]
    File        : trie.h
*/

#ifndef TRIE_H
#define TRIE_H

#define ALPHABET 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET];
    int isEnd;          // 1 if this node marks end of a word/key
} TrieNode;

typedef TrieNode* Trie;

// ADT style
/*
(i)  Create   → create empty Trie
(ii) Insert   → insert a string key
(iii) Search  → search for a key (returns 1 if found)
(iv) Destroy  → free entire Trie
*/

Trie createTrie();
void insertTrie(Trie root, const char *key);
int  searchTrie(Trie root, const char *key);
void destroyTrie(Trie root);

#endif