#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

typedef struct{
    int end; //if it is the end or not
    TrieNode * children[ALPHABET_SIZE]; //children, ascii index will tell if TrieNode of that value exists
} TrieNode;

typedef struct{
    // root which points to the whole structure
    TrieNode * root;
    int wordCount;
} Trie;

// definitions
// supports insert, search, prefixSearch, number of words

void insert(Trie * trie, char * target);
int search(Trie * trie, char * target);
int prefixSearch(Trie * trie, char * target);
int numberOfWords(Trie * trie);

// ctors, dtors
TrieNode * TrieNode_ctor();
Trie * Trie_ctor();
void TrieNode_dtor(TrieNode * node);
void Trie_dtor(Trie * trie);

// interface
TrieNode * TrieNode_ctor(){
    TrieNode * res = (TrieNode *)malloc(sizeof(TrieNode));
    
    // innit each trieNode in children
    for(int i = 0; i < ALPHABET_SIZE; ++i){
        res->children[i] = NULL;
    }

    res->end = 0; //false

    return res;
}

Trie * Trie_ctor(){
    Trie * res = (Trie *)malloc(sizeof(Trie));
    res->root = TrieNode_ctor();
    res->wordCount = 0;

    return res;
}

void insert(Trie * trie, char * target){
    if(trie == NULL) return;

    int length = strlen(target);
    TrieNode * level = trie->root;

    for(int i = 0; i < length; ++i){
        if(level->children[target[i] - 'a'] == NULL){
            level->children[target[i] - 'a'] = TrieNode_ctor(target[i]);
        }//if ascii index doesn't exist, make a trienode there

        level = level->children[target[i] - 'a'];
    }

    // increment word count
    if(!level->end) trie->wordCount++;

    level->end = 1; //indicates end of a string
}

int search(Trie * trie, char * target){
    if(trie == NULL) return 0; //false, doesn't exist

    int length = strlen(target);
    TrieNode * level = trie->root;

    for(int i = 0; i < length; ++i){
        if(level->children[target[i] - 'a'] == NULL){
            return 0;
        }//if character doesn't exist, then string doesn't exist

        level = level->children[target[i] - 'a'];
    }

    return level->end;
}

int prefixSearch(Trie * trie, char * target){
    if(trie == NULL) return 0; //false, doesn't exist

    int length = strlen(target);
    TrieNode * level = trie->root;

    for(int i = 0; i < length; ++i){
        if(level->children[target[i] - 'a'] == NULL){
            return 0;
        }//if character doesn't exist, then string doesn't exist

        level = level->children[target[i] - 'a'];
    }

    return 1;
}

int numberOfWords(Trie * trie){
    return trie->wordCount;
}

void TrieNode_dtor(TrieNode * node){
    // recursive, or standard
    // base case:
    // can't do end since cat and cattle, cat -> end, we don't deallocate tle
    // loop through each element until all of its null, ensuring that we've hit last level
    if (node == NULL) return;

    for(int i = 0; i < ALPHABET_SIZE; ++i){
        if(node->children[i] != NULL){
            // recurse down
            TrieNode_dtor(node->children[i]);
        }
    }

    free(node);
}

void Trie_dtor(Trie * trie){
    TrieNode_dtor(trie->root); //frees the root, but not the trie
    free(trie);
}
