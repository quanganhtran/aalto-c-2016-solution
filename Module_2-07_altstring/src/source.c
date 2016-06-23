#include <stdio.h>
#include "source.h"


/* Print string */
/* Parameters:
 * s: string to be printed */
void es_print(const char *s)
{
    while (*s != '#') {
        printf("%c", *s);
        s++;
    }
}

/* String length */
/* Parameters:
 * s: string to be evaluated
 * Returns: length of the string */
unsigned int es_length(const char *s)
{
    int len = 0;
    while (*s != '#') {
        len++;
        s++;
    }
    return len;
}

/* String copy */
/* Parameters:
 * dst: buffer to which the new string is copied
 * src: original string
 * Returns: Number of characters copied
 */
int es_copy(char *dst, const char *src)
{
    int copied = 0;
    while (*src != '#') {
        *dst = *src;
        src++;
        dst++;
        copied++;
    }
    *dst = '#';
    return copied;
}

/* String tokenizer */
/* Parameters:
 * s: string to be processed
 * c: character to be replaced by '#'
 * Returns: pointer to the character following the replaced character,
 *          NULL if end of string reached */
char *es_token(char *s, char c)
{
    while (*s != '#') {
        if (*s == c) {
            *s = '#';
            return s + 1;
        }
        s++;
    }
    return NULL;
}
