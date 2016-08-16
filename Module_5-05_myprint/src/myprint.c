#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "myprint.h"

int myprint(const char *format, ...)
{
    int arg_len = 0;
    char* find = strchr(format, '&');
    while (find) {
        arg_len++;
        find = strchr(find + 1, '&');
    }
    va_list args;
    va_start(args, format);
    // Make sure va_arg is not called past the argument list
    int arg_i = 0;
    for (size_t i = 0; i < strlen(format); i++) {
        char to_print = format[i];
        if (to_print == '&' && arg_i < arg_len) {
            printf("%d", va_arg(args, int));
            arg_i++;
        } else {
            fputc(to_print, stdout);
        }
    }
    va_end(args);
    return arg_len;
}