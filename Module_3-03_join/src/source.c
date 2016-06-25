#include <stdlib.h>
#include <string.h>
#include "source.h"

int* join_arrays(unsigned int len1, int* arr1, unsigned int len2, int* arr2, unsigned int len3, int* arr3)
{
    int* arr = malloc((len1 + len2 + len3) * sizeof(int));
    memcpy(arr, arr1, len1 * sizeof(int));
    memcpy(arr + len1, arr2, len2 * sizeof(int));
    memcpy(arr + len1 + len2, arr3, len3 * sizeof(int));
    return arr;
}