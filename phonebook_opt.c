#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "phonebook_opt.h"

hashTable *createHashTable(tableSize size)
{
    hashTable *ht = NULL;
    int i;

    // Allocate Hash Table
    if ((ht = (hashTable *) malloc(sizeof(hashTable))) == NULL)
        return NULL;

    // Allocate Entry
    if ((ht->hashEntry = (entry **) malloc(sizeof(entry*)*size)) == NULL)
        return NULL;

    // Allocate Head of list
    for (i = 0; i < size; i++) {
        ht->hashEntry[i] = NULL;
    }

    ht->size = size;
    return ht;
}

size_t hash(char *lastName, hashTable *ht)
{
    size_t hash_val = 0;
    while (*lastName != '\0')
        hash_val += *lastName++;
    return hash_val % ht->size;
}

entry *findName(char lastName[], hashTable *ht)
{
    entry *tmpEntry;
    size_t hashIndex = hash(lastName, ht);
    for (tmpEntry = ht->hashEntry[hashIndex]; tmpEntry != NULL; tmpEntry = tmpEntry->pNext) {
        if (strcmp(lastName, tmpEntry->lastName) == 0) {
            return tmpEntry;
        }
    }
    return NULL;
}

entry *append(char lastName[], hashTable *ht)
{
    size_t hashIndex = hash(lastName, ht);

    entry *newEntry;
    if ((newEntry = (entry *) malloc(sizeof(entry))) == NULL)
        return NULL;

    // Append
    strcpy(newEntry->lastName, lastName);
    newEntry->pNext = ht->hashEntry[hashIndex];
    ht->hashEntry[hashIndex] = newEntry;
    return newEntry;
}
