#include <stdio.h>
#include "filestats.h"


/* Returns the line count in given file
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * The number of lines in file. */
int line_count(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        return -1;
    }
    int line = 0, empty = 1;
    int status = fgetc(f);
    while (status >= 0) {
        if (status == '\n') {
            // Count a line, marking the next line as empty at this point
            empty = 1;
            line++;
        } else {
            // Mark that the current line is not empty
            empty = 0;
        }
        status = fgetc(f);
    }
    // Count the last line, if non-empty
    line += 1 - empty;
    if (fclose(f) < 0) {
        return -1;
    }
    return line;
}


/* Count the number of words in the file. Word has to include at least one
 * alphabetic character, and words are separated by whitespace.
 * 
 * Parameters:
 * filename: name of the file to be investigated.
 * 
 * Returns:
 * number of words in the file */
int word_count(const char *filename)
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        return -1;
    }
    int word = 0, in_word = 0;
    int status = fgetc(f);
    while (status >= 0) {
        if ((65 <= status && status <= 90) || (97 <= status && status <= 122)) {
            // Recognize a word when an alphabetic character is detected
            in_word = 1;
        } else if (status == ' ' || status == '\n') {
            // Count the word on whitespace, then acknowledge the word ending
            word += in_word;
            in_word = 0;
        }
        status = fgetc(f);
    }
    // Count the last word, if any
    word += in_word;
    if (fclose(f) < 0) {
        return -1;
    }
    return word;
}
