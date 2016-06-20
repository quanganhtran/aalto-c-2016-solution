#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "source.h"
 
/* Don't touch the definition of msgs array! Checker uses this. */
char *msgs[10] = {
    "'6=*w+~)._", "J65+~5+~=0/*69,~+9;,9*~19++=79"
};
 
 
void ascii_chart(char min, char max)
{
    for (int i = min; i <= max; i++) {
        printf("%3d 0x%02x ", i, i);
        if (isprint(i)) printf("%c", i);
        else printf("?");
        if ((i - min + 1) % 4) printf("\t");
        else printf("\n");
    }
}
 
char get_character(int msg, unsigned int cc) {
    if (msg >= 10 || !msgs[msg])
        return 0;
 
    if (strlen(msgs[msg]) <= cc)
        return 0;
     
    return msgs[msg][cc];
}
 
 
void secret_msg(int msg)
{
    int i = 0;
    char c = get_character(msg, i);
    while(c) {
        printf("%c", 158 - c);
        c = get_character(msg, ++i);
    }
}