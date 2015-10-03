#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include IMPL

#define DICT_FILE "./dictionary/words.txt"
#define ALL_NAME_FILE "./dictionary/all-names.txt"
#define FEMALE_NAME_FILE "./dictionary/female-names.txt"
#define MALE_NAME_FILE "./dictionary/male-names.txt"
#define PRIME_FILE "./dictionary/Prime-10000.csv"
#define TOLOWERCASE_FILE "./dictionary/tolowercase.c"

#define SEARCH_NAME "windy"

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(ALL_NAME_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    entry *root = NULL;
#if defined(__GNUC__)
    __builtin___clear_cache((char *) root, (char *) root + sizeof(entry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        if (root != NULL)
            append(line, root);
        else
            root = append(line, root);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);


    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = SEARCH_NAME;

    assert(findName(input, root) &&
           "Did you implement findName() in " IMPL "?");
    assert(0 == strcmp(findName(input, root)->lastName, SEARCH_NAME));

#if defined(__GNUC__)
    __builtin___clear_cache((char *) root, (char *) root + sizeof(entry));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
    findName(input, root);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);

    /* FIXME: release all allocated entries */
    free(root);

    return 0;
}