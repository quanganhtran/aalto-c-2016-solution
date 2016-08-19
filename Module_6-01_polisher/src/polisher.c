#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "polisher.h"

#define CHUNK 64

/* Read given file <filename> to dynamically allocated memory.
 * Return pointer to the allocated memory with file content, or
 * NULL on errors.
 */
char *read_file(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        return NULL;
    }
    char* buffer = malloc(CHUNK + 1);
    if (!buffer) {
        return NULL;
    }
    int pos = 0;
    char* status = fgets(buffer, CHUNK + 1, f);
    while (status) {
        int len = strlen(status);
        pos += len;
        char* new_buffer = realloc(buffer, pos + CHUNK + 1);
        if (!new_buffer) {
            free(buffer);
            return NULL;
        }
        buffer = new_buffer;
        status = fgets(buffer + pos, CHUNK + 1, f);
    }
    return buffer;
}


/* Remove C comments from the program stored in memory block <input>.
 * Returns pointer to code after removal of comments.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *remove_comments(char *input)
{
    char* res = malloc(strlen(input) + 1);
    if (!res) {
        return NULL;
    }
    char* read = input,
        * write = res;
    char c = *read,
         in_comment = 0;
    while (c) {
        if (c == '/' && !in_comment) {
            if (*(read + 1) == '/') {
                in_comment = 'l';
            } else if (*(read + 1) == '*') {
                in_comment = 'b';
            }
        } else if (c == '\n' && in_comment == 'l') {
            in_comment = 0;
            c = *(++read);
            continue;
        } else if (c == '*' && in_comment == 'b' && *(read + 1) == '/') {
            in_comment = 0;
            read += 2;
            c = *read;
            continue;
        }
        
        if (!in_comment) {
            *write = c;
            write++;
        }
        c = *(++read);
    }
    *write = c;
    free(input);
    return res;
}

/* Indent the C-code at memory block <indent>. String <pad> represents
 * one block of indentation. Only opening curly braces '{' increase the
 * indentation level, and closing curly braces '}' decrease the indentation level.
 * Return the pointer to the code after modification.
 * Calling code is responsible of freeing only the memory block returned by
 * the function.
 */
char *indent(char *input, const char *pad)
{
    int len = strlen(input);
    int pad_len = strlen(pad);
    char* res = malloc(len + 1);
    if (!res) {
        return NULL;
    }
    char* read = input,
        * write = res;
    char c = *read,
         indent = 0;
    while (c) {
        if (*(read + 1) == '}')
            indent--;
        if (c == '{') {
            indent++;
        } else if (c == '\n') {
            if (*(read + 1) == ' ' || *(read + 1) == '\t') {
                read++;
            }
            if (indent && *(read + 1) != '\n') {
                len += pad_len * indent;
                char* new_res = realloc(res, len + 1);
                if (!new_res) {
                    free(res);
                    return NULL;
                }
                write = new_res + (write - res);
                res = new_res;
                *write = c;
                write++;
                for (int i = 0; i < indent; i++) {
                    strncpy(write, pad, pad_len);
                    write += pad_len;
                }
                c = *(++read);
                continue;
            }
        }
        
        *write = c;
        write++;
        c = *(++read);
    }
    *write = c;
    free(input);
    return res;
}
