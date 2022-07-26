#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_NAME 20

#include <cglm/cglm.h>

typedef struct player_type
{
    int id;
    char username[PLAYER_NAME];
    vec2 position;
    vec2 velocity;
} player_t;

player_t *create_player();

void move_player(player_t *player, char *inputs);

#endif
