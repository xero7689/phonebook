#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#define DICT_FILE "./dictionary/words.txt"
#define FIND_NAME "zyxel"

static double diff_in_milisecond(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    entry *pHead, *e;
    pHead = (entry *) malloc(sizeof(entry));
    printf("size of entry : %lu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;
#if defined(OPTIMIZE)
    hashTable *ht = createHashTable(TABLE_SIZE);
    printf("Hash Table Size: %d\n", TABLE_SIZE);
#endif

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
#if defined(OPTIMIZE)
        e = append(line, ht);
#else
        e = append(line, e);
#endif
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_milisecond(start, end);

    /* close file as soon as possible */
    fclose(fp);

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = FIND_NAME;
    void *findPtr = NULL;
#if defined(OPTIMIZE)
    findPtr = ht;
#else
    findPtr = pHead;
#endif
    assert(findName(input, findPtr) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, findPtr)->lastName, "zyxel"));

#if defined(__GNUC__)
    __builtin___clear_cache((char *) pHead, (char *) pHead + sizeof(entry));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, findPtr);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_milisecond(start, end);

    printf("execution time of append() : %lf ms\n", cpu_time1);
    printf("execution time of findName() : %lf ms\n", cpu_time2);

    /* FIXME: release all allocated entries */
    free(pHead);

    return 0;
}
