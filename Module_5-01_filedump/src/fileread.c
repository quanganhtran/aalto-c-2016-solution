#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "fileread.h"

/* Prints the given file as text on the screen.
 * Only printable characters are shown. Non-printable characters are printed
 * as '?'. <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int textdump(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        return -1;
    }
    int read = 0;
    char c = fgetc(f);
    while (c >= 0) {
        if (isprint(c)) {
            printf("%c", c);
        } else {
            printf("?");
        }
        read++;
        c = fgetc(f);
    }
    if (fclose(f) < 0) {
        exit(EXIT_FAILURE);
    }
    return read;
}


/* Prints the given file as hexdump, at most 16 numbers per line.
 * <filename> parameter is the name of the file.
 * 
 * Returns the number of characters read
 */
int hexdump(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        return -1;
    }
    int read = 0, line = 16;
    int x = fgetc(f);
    while (x >= 0) {
        if (--line) {
            printf("%02x ", (unsigned int) x);
        } else {
            printf("%02x \n", (unsigned int) x);
            line = 16;
        }
        read++;
        x = fgetc(f);
    }
    if (fclose(f) < 0) {
        exit(EXIT_FAILURE);
    }
    return read;
}
