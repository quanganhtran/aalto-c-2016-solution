#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "strarray.h"

/* Exercise a: Initializes the string array to contain the initial
 * NULL pointer, but nothing else.
 * Returns: pointer to the array of strings that has one element
 *      (that contains NULL)
 */
char **init_array(void)
{
    char** arr = malloc(sizeof(*arr));
    arr[0] = NULL;
    return arr;
}

/* Releases the memory used by the strings.
 */
void free_strings(char **array)
{
    char** ite = array;
    while(*ite) {
        free(*ite);
        ite++;
    }
    free(array);
}

/* Exercise b: Add <string> to the end of array <array>.
 * Returns: pointer to the array after the string has been added.
 */
char **add_string(char **array, const char *string)
{
    /* Get the index of the last element (the NULL pointer), which can determine
     * the array current length. This operation is in O(n)
     * Since no other information about the array is passed to the function,
     * the only possible O(1) approach is to allocate extra memory in the array
     * to store its current length, and offset accordingly. This might introduce
     * bugs to the program.
     */
    int old_last = 0;
    while(array[old_last]) {
        old_last++;
    }
    // Increase the size of the array.
    // Abort the program if this operation fails.
    char** new_array = realloc(array, sizeof(*array) * (old_last + 2));
    if (!new_array) {
        free_strings(array);
        exit(EXIT_FAILURE);
    }
    array = new_array;
    // Copy the string to the new location, which is the previous last index.
    size_t str_len = strlen(string);
    array[old_last] = malloc(str_len + 1);
    memcpy(array[old_last], string, str_len + 1);
    // Terminate the new array with a NULL pointer
    array[old_last + 1] = NULL;
    return array;
}

/* Exercise c: Convert letters of all strings in <array> to lower case.
 */
void make_lower(char **array)
{
    for (; *array; array++) {
        char* str = *array;
        for (; *str; str++) {
            *str = tolower(*str);
        }
    }
}


/* Exercise d: reorder strings in <array> to lexicographical order */
void sort_strings(char **array)
{
    // Insertion sort
    for (int i = 0; array[i]; i++) {
        char* el = array[i];
        int pos;
        for (pos = i - 1; pos >= 0; pos--) {
            if (strcmp(el, array[pos]) < 0) {
                array[pos + 1] = array[pos];
            } else {
                break;
            }
        }
        array[pos + 1] = el;
    }
}

/* You can use this function to check what your array looks like.
 */
void print_strings(char **array)
{
    if (!array)
        return;
    while (*array) {
        printf("%s  ", *array);
        array++;
    }
    printf("\n");
}
