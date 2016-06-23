#include "source.h"


/* Insertion sort */
/* Parameters:
 * start: start of an array
 * size: length of an array
 */
void sort(int *start, int size)
{
    for (int i = 0; i < size; i++) {
        int el = start[i];
        int pos;
        for (pos = i - 1; pos >= 0; pos--) {
            if (el < start[pos]) {
                start[pos + 1] = start[pos];
            } else {
                break;
            }
        }
        start[pos + 1] = el;
    }
}

