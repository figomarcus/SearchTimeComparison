/*
    Name        : [Figo Marcus Fernandes]
    Class       : [MSc AI]
    Roll Number : [2604]
    File        : trie.h
        Date Created: 30/09/26
    Date Modified: 30/09/26
*/


#ifndef TRIE_H
#define TRIE_H

#define ALPHABET 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET];
    int isEnd;
} TrieNode;

typedef TrieNode* Trie;

Trie createTrie();
void insertTrie(Trie root, const char *key);
int  searchTrie(Trie root, const char *key);
void destroyTrie(Trie root);

#endif
/*
=====================================================
ADT SPECIFICATION FOR TRIE
=====================================================

(i) Create (trie)
1. Function/Purpose
   To create and initialize an empty Trie.
2. Pre-condition
   Sufficient memory must be available.
3. Input
   None
4. Output
   trie (Trie)
5. Post-condition
   An empty Trie is successfully created.

(ii) Insert (trie, key)
1. Function/Purpose
   To insert a string key into the Trie.
2. Pre-condition
   The Trie must exist.
   Sufficient memory must be available.
3. Input
   trie (Trie)
   key (string)
4. Output
   trie (Trie)
5. Post-condition
   The key is inserted into the Trie.
   isEnd of the last node is set to 1.

(iii) Search (trie, key)
1. Function/Purpose
   To search whether a given key exists in the Trie.
2. Pre-condition
   The Trie must exist.
3. Input
   trie (Trie)
   key (string)
4. Output
   flag (boolean)   // 1 if found, 0 if not found
5. Post-condition
   Structure of the Trie remains unchanged.

(iv) Destroy (trie)
1. Function/Purpose
   To destroy the entire Trie and free all memory.
2. Pre-condition
   The Trie must exist.
3. Input
   trie (Trie)
4. Output
   trie (Trie)
5. Post-condition
   All nodes are freed and the Trie becomes empty.
=====================================================
*/