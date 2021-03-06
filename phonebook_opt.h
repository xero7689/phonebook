#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define OPT
#define MAX_LAST_NAME_SIZE 16
#define TABLE_SIZE 42737

typedef unsigned int tableSize;

/* Hash version */
typedef struct __DETAIL_ENTRY {
    char firstName[16];
    char email[16];
    char addr1[16];
    char addr2[16];
    char city[16];
    char phone[10];
    char zip[5];
    char cell[10];
    char state[2];
   
} phonebook_detail;

typedef struct __PHONE_BOOK_ENTRY {
   char lastName[MAX_LAST_NAME_SIZE];
   phonebook_detail *detail;
   struct __PHONE_BOOK_ENTRY *pNext;
} entry;

typedef struct __HASH_TABLE {
    tableSize size;
    entry** hashEntry;
} hashTable;

hashTable *createHashTable(tableSize size);
size_t hash(char *lastName, hashTable *ht);
entry *findName(char lastname[], hashTable *ht);
entry *append(char lastName[], hashTable *ht);
int freeHashTable(hashTable *ht);

#endif
