#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_NAME 20

typedef struct player_type
{
    int id;
    char username[PLAYER_NAME];
} player_t;

player_t *create_player();

void move_player(char *inputs);

#endif
