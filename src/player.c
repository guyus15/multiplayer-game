/**
 * @file player.h
 * @brief A file which specifies related functions for the player.
 */

#include <player.h>
#include <stdlib.h>
#include <string.h>

player_t *create_player()
{
    player_t *player = (player_t *) malloc(sizeof(player_t));
    
    // Zero all values.
    player->id = 0;
    memset(player->username, 0, sizeof(player->username));

    return player;
}
