#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
        free(ite);
        ite++;
    }
    free(array);
}

/* Exercise b: Add <string> to the end of array <array>.
 * Returns: pointer to the array after the string has been added.
 */
char **add_string(char **array, const char *string)
{
    size_t new_len = sizeof(array) / sizeof(*array) + 1;
    array = realloc(array, sizeof(*array) * new_len);
    
    size_t str_len = strlen(string);
    array[new_len - 2] = malloc(str_len + 1);
    memcpy(array[new_len - 2], string, str_len + 1);
    
    array[new_len - 1] = NULL;
    return array;
}

/* Exercise c: Convert letters of all strings in <array> to lower case.
 */
void make_lower(char **array)
{
    (void) array; // replace this
}


/* Exercise d: reorder strings in <array> to lexicographical order */
void sort_strings(char **array)
{
    (void) array;
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
