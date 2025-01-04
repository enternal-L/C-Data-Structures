#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Make a hash_table that deals with collision
// hash function can be ok, want to see intuition

typedef struct{
    char * key;
    int value;
    HashNode * next;
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
    
    if(ht->table[index] == NULL){
        // do the insertion
        ht->table[index]->key = key;
        ht->table[index]->value = value;
    }//if it is empty, we insert right here

    else{
        HashNode * current = ht->table[index];

        while(current->next != NULL){
            current = current->next;
        }

        // insert the node to next of current
        HashNode * temp;
        temp->key = key;
        temp->value = value;

        current->next = temp;

        return current->next;
    }//if it isn't empty, go to end of LL

    return NULL;
}

HashNode * Search(HashTable *ht, char * key){
    if(ht == NULL || key == NULL) return NULL;

    unsigned int index = hash(key);

    if(ht->table[index] == NULL){
        return NULL;
    }//if we hit an empty, key was never here

    else{
        HashNode * current = ht->table[index];

        while(current){
            if(strcmp(current->key, key) == 0){
                return current;
            }//we get a hit

            current = current->next;
        }
    }//node hit

    return NULL;
}

void Delete(HashTable * ht, char * key){
    if(ht == NULL || key == NULL) return NULL;

    unsigned int index = hash(key);

    if(ht->table[index] == NULL){
        return;
    }//if we hit an empty, key was never here nothing to delete

    else{
        HashNode * current = ht->table[index];

        while(current->next){
            if(strcmp(current->next->key, key) == 0){
                current->next = NULL;
            }//we get a hit

            current = current->next;
        }
    }//node hit
}



