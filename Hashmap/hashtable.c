#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct HashTable {
    int table[TABLE_SIZE];
} HashTable;

// Function prototypes
HashTable* createHashTable();
unsigned int hash(const char* key);
void insert(HashTable* ht, const char* key, int value);
int search(HashTable* ht, const char* key);
void delete(HashTable* ht, const char* key);
void freeHashTable(HashTable* ht);

int main() {
    
    printf("Name of %s, has hash value of %d\n", "Jacob", hash("Jacob"));
    printf("Name of %s, has hash value of %d\n", "Emily", hash("Emily"));
    printf("Name of %s, has hash value of %d\n", "Thomas", hash("Thomas"));

    return 0;
}

// assume an ok hash function
unsigned int hash(const char* key){
    unsigned int length = strlen(key);
    unsigned int res = 0;
    
    for(int i = 0; i < length; ++i){
        res += key[i];
        res *= key[i];
    }

    return res % TABLE_SIZE;
}

HashTable* createHashTable(){
    HashTable * res = (HashTable * )malloc(sizeof(HashTable)); //doing new

    for(int i = 0; i < TABLE_SIZE; ++i){
        res->table[i] = NULL;
    }

    return res;
}

void insert(HashTable* ht, const char* key, int value){

    if(key == NULL) return;

    // check if it exists in table
    unsigned int index = hash(key);

    if(ht->table[index] == NULL){
        // insert
        ht->table[index] = value;
    }

    else{
        // collision
    }
}

int search(HashTable* ht, const char* key){
    // has to deal with collisions
    // Assume that user passes in valid key -> 1. it's not null 2. it is in the table
    return ht->table[hash(key)];
}

void delete(HashTable* ht, const char* key){
    // we have an array of integers
    // dealing with collisions: we indicate -> deletion, empty, etc.
}