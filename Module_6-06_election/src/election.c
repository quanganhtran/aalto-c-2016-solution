#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "election.h"

#define NAME_LEN 40

int upvote(struct votes* arr, char* name, int len);
int leads(const void* cand1, const void* cand2);

struct votes *read_votes(const char *filename) {
    FILE* f = fopen(filename, "r");
    if (!f)
        return NULL;
    
    int len = 0;
    // Create an empty candidate, which is not counted towards the length of the dynamic array
    struct votes* vote_arr = calloc(len + 1, sizeof(*vote_arr));
    vote_arr[0].name[0] = '\0';
    vote_arr[0].votes = 0;
    // buffer holds the name and the newline character
    char buffer[NAME_LEN + 1], name[NAME_LEN];
    char* status = fgets(buffer, NAME_LEN + 1, f);
    while (status) {
        sscanf(buffer, "%s\n", name);
        if (upvote(vote_arr, name, len)) {
            // Extend the dynamic array to include the new candidate
            len++;
            struct votes* new_arr = realloc(vote_arr, (len + 1) * sizeof(*vote_arr));
            if (!new_arr) {
                free(vote_arr);
                return NULL;
            }
            vote_arr = new_arr;
            strncpy(vote_arr[len - 1].name, name, NAME_LEN);
            vote_arr[len - 1].votes = 1;
            vote_arr[len].name[0] = '\0';
            vote_arr[len].votes = 0;
        }
        status = fgets(buffer, NAME_LEN + 1, f);
    }
    if (fclose(f) < 0) {
        free(vote_arr);
        return NULL;
    }
    return vote_arr;
}

/* Increase the vote of the candidate of <name> by one
 * Return 0 if the candidate is found within the first <len> of <arr>,
 * otherwise return 1
 */
int upvote(struct votes* arr, char* name, int len) {
    for (int i = 0; i < len; i++) {
        if (strcmp(arr[i].name, name) == 0) {
            arr[i].votes++;
            return 0;
        }
    }
    return 1;
}

void results(struct votes *vlist) {
    int len = 0;
    while (vlist[len].votes) {
        len++;
    }
    qsort(vlist, len, sizeof(*vlist), leads);
    for (int i = 0; i < len; i++) {
        printf("%s: %d\n", vlist[i].name, vlist[i].votes);
    }
}

/* The comparator to sort the candidate descending by votes, or ascending lexicographically
 */
int leads(const void* cand1, const void* cand2) {
    const struct votes* c1 = cand1,
                      * c2 = cand2;
    int dvote = c2->votes - c1->votes;
    if (dvote)
        return dvote;
    return strcmp(c1->name, c2->name);
}