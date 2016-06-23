#include <string.h>
#include "source.h"


/* Korsoraattori
 */
void korsoroi(char *dest, const char *src)
{
    int word = 0;
    while (*src) {
        if (*src == 'k' && *(src + 1) == 's') {
            // Replace "ks" with "x", move src two chars ahead
            *dest = 'x';
            src += 2;
        } else if (*src == 't' && *(src + 1) == 's') {
            // Replace "ts" with "z", move src two chars ahead
            *dest = 'z';
            src += 2;
        } else if (*src == ' ') {
            word++;
            if (word % 3 == 0) {
                strncpy(dest, " niinku", 7);
                dest += 7; // Immediately move dest past the insertion
            } else if (word % 4 == 0) {
                strncpy(dest, " totanoin", 9);
                dest += 9; // Immediately move dest past the insertion
            }
            *dest = ' ';
            src++;
        } else {
            *dest = *src;
            src++;
        }
        dest++; // Move dest past the newly copied char
    }
    *dest = '\0';
}
