#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Make a hash_table that deals with collision
// hash function can be ok, want to see intuition

typedef struct{
    char * key;
    int value;
    int label;
} HashNode;

typedef struct{
    HashNode * table[TABLE_SIZE];
} HashTable;

// definitions
unsigned int hash(char * key);
HashNode * Insert(HashTable *ht, char * key, int value);
HashNode * Search(HashTable *ht, char * key);
void Delete(HashTable * ht, char * key);

// Labels:
// Occupied, Deleted, Empty
// 0, 1, 2

unsigned int hash(char * key){
    unsigned int res = 0;
    unsigned int length = strlen(key);

    for(int i = 0; i < length; ++i){
        res += key[i];
        res *= key[i];
    }

    return res % 10;
}

HashNode * Insert(HashTable *ht, char * key, int value){
    if(ht == NULL || key == NULL) return NULL;

    unsigned int index = hash(key);
    
    for(int i = 0; i < TABLE_SIZE; ++i){
        if(ht->table[index + i % TABLE_SIZE] == NULL || ht->table[index + i % TABLE_SIZE]->label){
            // do the insertion
            ht->table[index + i % TABLE_SIZE]->key = key;
            ht->table[index + i % TABLE_SIZE]->value = value;
            ht->table[index + i % TABLE_SIZE]->label = 0;
        }

        if(strcmp(ht->table[index + i % TABLE_SIZE]->key, key)){
            return NULL;
        }
    }

    return NULL;
}

HashNode * Search(HashTable *ht, char * key){
    if(ht == NULL || key == NULL) return NULL;

    unsigned int index = hash(key);

    for(int i = 0; i < TABLE_SIZE; ++i){
        if(ht->table[index + i % TABLE_SIZE] == NULL){
            return NULL;
        }//if we hit an empty, key was never here

        else{
            if(strcmp(ht->table[index + i % TABLE_SIZE]->key, key) && !ht->table[index + i % TABLE_SIZE]->label){
                return ht->table[index + i % TABLE_SIZE];
            }//if key matches and it is occupied, return value
        }//node hit
    }

    return NULL;
}

void Delete(HashTable * ht, char * key){
    if(ht == NULL || key == NULL) return NULL;

    unsigned int index = hash(key);

    for(int i = 0; i < TABLE_SIZE; ++i){
        if(ht->table[index + i % TABLE_SIZE] == NULL){
            return;
        }//if we hit an empty, key was never here nothing to delete

        else{
            if(strcmp(ht->table[index + i % TABLE_SIZE]->key, key) && !ht->table[index + i % TABLE_SIZE]->label){
                ht->table[index + i % TABLE_SIZE]->label = 1;
                return;
            }//if key matches and it is occupied, return value
        }//node hit
    }
}



