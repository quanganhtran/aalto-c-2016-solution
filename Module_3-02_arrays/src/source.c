#include <stdlib.h>
#include <stdio.h>
#include "source.h"


/* Dynamic Array Reader */
/* Parameters:
 * n: Number of values to be read
 * 
 * Returns: pointer to the dynamically allocated array
 */
int *dyn_reader(unsigned int n)
{
    int* arr = malloc(sizeof(int) * n);
    if (!arr) return NULL;
    for (unsigned int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    return arr;
}

/* Add to array */
/* Parameters:
 * arr: Existing array of integers
 * num: number of integers in the array before the call
 * newval: new value to be added
 * 
 * Returns: pointer to the allocated array
 */
int *add_to_array(int *arr, unsigned int num, int newval)
{
    int* newarr = realloc(arr, sizeof(int) * (num + 1));
    if (!newarr) return NULL;
    newarr[num] = newval;
    return newarr;
}
