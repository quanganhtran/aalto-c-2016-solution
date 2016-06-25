#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "source.h"


struct vessel create_vessel(const char *p_name,
			    double p_length,
			    double p_depth,
			    struct cargo p_crg)
{
    struct vessel ship = { "", p_length, p_depth, p_crg };
    strncpy(ship.name, p_name, 31);
    ship.name[30] = '\0';
    return ship;
}

void print_vessel(const struct vessel *ship)
{
    printf("%s\n", ship->name);
    printf("%.1f\n", ship->length);
    printf("%.1f\n", ship->depth);
    printf("%s\n", ship->crg.title);
    printf("%d\n", ship->crg.quantity);
    printf("%.1f\n", ship->crg.weight);
}
