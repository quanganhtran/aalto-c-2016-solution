#include <stdio.h>
#include "source.h"


#ifndef MAWKKE
// longer solution by Pasi

/* 03-mastermind
 * Implementation with O(kn) time complexity (constant k)
 */
void mastermind(const int *solution, const int *guess, char *result, unsigned int len)
{
    int i;
    for (i = 0; i < len; i++) {
        result[i] = ' ';
    }
    int count[10] = { 0 };
    for (i = 0; i < len; i++) {
        count[solution[i]]++;
    }
    for (i = 0; i < len; i++) {
        if (guess[i] == solution[i]) {
            result[i] = '+';
            count[guess[i]]--;
        }
    }
    for (i = 0; i < len; i++) {
        if (result[i] == '+') continue;
        if (count[guess[i]] > 0) {
            result[i] = '*';
            count[guess[i]]--;
        } else {
            result[i] = '-';
        }
    }
}
#endif
