#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastName[], entry *root)
{
    entry *tmp = root;
    //int depth = 0;  // for debug
    while (tmp != NULL) {
        if (strcmp(lastName, tmp->lastName) > 0) {
            tmp = tmp->pRight;
            //depth++;
        } else if (strcmp(lastName, tmp->lastName) < 0) {
            tmp = tmp->pLeft;
            //depth++;
        } else {
            //printf("Name: %s at depth %d\n", lastName, depth);
            return tmp;
        }
    }
    return NULL;
}

entry *append(char lastName[], entry *root)
{
    if (root != NULL) {
        entry *tmp = root;
        while (tmp != NULL) {
            if (strcmp(lastName, tmp->lastName) > 0) {
                if (tmp->pRight != NULL)
                    tmp = tmp->pRight;
                else {
                    tmp->pRight = (entry*)malloc(sizeof(entry));
                    strcpy(tmp->lastName, lastName);
                    tmp->pRight->pLeft = tmp->pRight->pRight = NULL;
                }
            } else if (strcmp(lastName, tmp->lastName) < 0) {
                if (tmp->pLeft != NULL)
                    tmp = tmp->pLeft;
                else {
                    tmp->pLeft = (entry*)malloc(sizeof(entry));
                    strcpy(tmp->lastName, lastName);
                    tmp->pLeft->pLeft = tmp->pLeft->pRight = NULL;
                }
            } else {
                return NULL;  // Duplicate entry!
            }
        }
        return tmp;
    } else {
        root = (entry*)malloc(sizeof(entry));
        strcpy(root->lastName, lastName);
        root->pLeft = root->pRight = NULL;
        return root;
    }
    return NULL;
}
