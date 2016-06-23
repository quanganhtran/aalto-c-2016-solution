#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "source.h"


/* Print string array, last element is NULL */
/* Parameters:
 * array: string array to be printed, each string on own line */
void print_strarray(char *array[])
{
    for (int i = 0; array[i] != NULL; i++) {
        char* str_p = array[i];
        while (*str_p) {
            printf("%c", *str_p);
            str_p++;
        }
        printf("\n");
    }
}

/* Put strings from string separated by space to a string array */
/* Parameters:
 * string: string to be cut into parts and placed into the array, 
   remember to add ending zeros '\0' for strings and NULL to the end of the whole array!
 * arr: ready-made array that the strings will be put into */
void str_to_strarray(char* string, char** arr)
{
    int i = 0, j = 0, has_char = *string ? 1 : 0;
    while (*string) {
        if (*string == ' ') {
            arr[i][j] = '\0';
            i++;
            j = 0;
        } else {
            arr[i][j] = *string;
            j++;
        }
        string++;
    }
    // When the end of string is met
    if (has_char) {
        arr[i][j] = '\0';
        arr[i + 1] = NULL;
    } else {
        arr[0] = NULL;
    }
    
}
