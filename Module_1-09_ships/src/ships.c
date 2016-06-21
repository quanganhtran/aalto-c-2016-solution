#include <stdio.h>
#include <stdlib.h>
#include "ships.h"

const unsigned int xsize = 10;
const unsigned int ysize = 10;
const unsigned int shiplen = 3;

/* implement these functions */

/* Task a: Place <num> ships on the game map.
 */
void set_ships(unsigned int num)
{
    int n = 0;
    while (n < num) {
        if (place_ship(rand() % 10, rand() % 10, rand() % 2)) n++;
    }
}


/* Task b: print the game field
 */
void print_field(void)
{
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {
            if (is_visible(x, y)) printf("%c", is_ship(x, y));
            else printf("?");
        }
        printf("\n");
    }
}


/* Task c: Ask coordinates (two integers) from user, and shoot the location.
 * Returns -1 if user gave invalid input or coordinates, 0 if there was no ship
 * at the given location; and 1 if there was a ship hit at the location.
 */
int shoot(void)
{
    int x, y;
    scanf("%d %d", &x, &y);
    if (x < 0 || x >= xsize || y < 0 || y >= ysize) return -1;
    checked(x, y);
    if (is_ship(x, y) == '+') {
        hit_ship(x, y);
        return 1;
    }
    return 0;
}

/* Task d: Returns 1 if game is over (all ships are sunk), or 0 if there
 * still are locations that have not yet been hit. <num> is the number of
 * ships on the game map. It is assumed to be the same as in the call to
 * set_ships function.
 */
int game_over(unsigned int num)
{
    int shot = 0;
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {
            if (is_ship(x, y) == '#') shot++;
        }
    }
    if (shot >= num * 3) return 1;
    return 0;
}
