/* monster.c -- Implementation of monster actions
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dungeon.h"

// for defining some monster types below that can be used in the game
typedef struct {
    char name[20];  // Name of monster
    char sign;  // character to show it on map
    unsigned int hplow;  // lowest possible initial maxhp
    unsigned int hphigh;  // highest possible initial maxhp
} MonstType;

// Specifying three monster types to start with.
// Feel free to add more, or change the below
// Note that it is up to you to decide whether to use this array from createMonsters
// you may or may not use it
const MonstType types[] = {
    { "Goblin", 'G', 6, 10},
    { "Rat", 'R', 3, 5},
    { "Dragon", 'D', 15, 20}
};


/* One kind of attack done by monster.
 * The attack function pointer can refer to this.
 * 
 * Parameters:
 * game: the game state
 * monst: The monster performing attack
 */
void attackPunch(Game *game, Creature *monst) {
    printf("%s punches you! ", monst->name);
    int hitprob = 50;
    int maxdam = 4;
    if (rand() % 100 < hitprob) {
        printf("Hit! ");
        int dam = rand() % maxdam + 1;
        printf("Damage: %d ", dam);
        game->hp = game->hp - dam;
        if (game->hp <= 0)
            printf("You died!");
        printf("\n");
    } else {
        printf("Miss!\n");
    }
}

/* Add character location check to isBlocked
 */
int monsterIsBlocked(Game *game, int x, int y) {
    return isBlocked(game, x, y) || (x == game->position.x && y == game->position.y);
}

/* Exercise (c)
 *
 * Move monster 'monst' towards the player character.
 * See exercise description for more detailed rules.
 */
void moveTowards(Game *game, Creature *monst) {
    int x = monst->pos.x, y = monst->pos.y;
    if (x < game->position.x && !monsterIsBlocked(game, x + 1, y)) {
        x++;
    } else if (x > game->position.x && !monsterIsBlocked(game, x - 1, y)) {
        x--;
    } else if (y < game->position.y && !monsterIsBlocked(game, x, y + 1)) {
        y++;
    } else if (y > game->position.y && !monsterIsBlocked(game, x, y - 1)) {
        y--;
    }
    monst->pos = (Point){x, y};
}

/* Exercise (d)
 *
 * Move monster 'monst' away from the player character.
 * See exercise description for more detailed rules.
 */
void moveAway(Game *game, Creature *monst) {
    int x = monst->pos.x, y = monst->pos.y;
    if (x < game->position.x && !isBlocked(game, x - 1, y)) {
        x--;
    } else if (x > game->position.x && !isBlocked(game, x + 1, y)) {
        x++;
    } else if (y < game->position.y && !isBlocked(game, x, y - 1)) {
        y--;
    } else if (y > game->position.y && !isBlocked(game, x, y + 1)) {
        y++;
    }
    monst->pos = (Point){x, y};
}


/* Exercise (e)
 *
 * Take action on each monster (that is alive) in 'monsters' array.
 * Each monster either attacks or moves (or does nothing if no action is specified)
 */
void monsterAction(Game *game) {
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        Creature *m = &game->monsters[i];
        if (abs(sqrt(pow(m->pos.x - game->position.x, 2) + pow(m->pos.y - game->position.y, 2)) - 1) < 0.1) {
            m->attack(game, m);
        } else {
            m->move(game, m);
        }
    }
}


/* Exercise (b)
 *
 * Create opts.numMonsters monsters and position them on valid position
 * in the the game map. The moster data (hitpoints, name, map sign) should be
 * set appropriately (see exercise instructions) 
 */
void createMonsters(Game *game) {
    unsigned int n = game->opts.numMonsters;
    game->numMonsters = 0;
    game->monsters = malloc(n * sizeof(*game->monsters));
    Creature* mons = game->monsters;
    unsigned int w = game->opts.mapWidth;
    unsigned int h = game->opts.mapHeight;
    for (unsigned int i = 0; i < n; i++) {
        Creature* mon = &mons[i];
        // Generate a random valid position for the monster
        int x = rand() % w, y = rand() & h;
        while (isBlocked(game, x, y)) {
            x = rand() % w;
            y = rand() & h;
        }
        mon->pos = (Point){x, y};
        // Select a random type for the monster, which determine its name, sign and maxhp
        MonstType type = types[rand() % 3];
        strncpy(mon->name, type.name, 20);
        mon->sign = type.sign;
        mon->maxhp = rand() % (type.hphigh - type.hplow) + type.hplow;
        mon->hp = mon->maxhp;
        // Select default behaviors for the monster
        mon->move = moveTowards;
        mon->attack = attackPunch;
        // Increase the monster count
        game->numMonsters++;
    }
}

/* Determine whether monster moves towards or away from player character.
 */
void checkIntent(Game *game)
{
    for (unsigned int i = 0; i < game->numMonsters; i++) {
        Creature *m = &game->monsters[i];
        if (m->hp <= 2) {
            m->move = moveAway;
        } else {
            m->move = moveTowards;
        }
        if (m->hp < m->maxhp)
            m->hp = m->hp + 0.1;  // heals a bit every turn
    }
}
