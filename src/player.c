/**
 * @file player.h
 * @brief A file which specifies related functions for the player.
 */

#include <player.h>
#include <input.h>
#include <stdlib.h>
#include <string.h>

/**
 * Create a player object.
 * 
 * @return player_t* A pointer to the created player.
 */
player_t *create_player()
{
    player_t *player = (player_t *) malloc(sizeof(player_t));
    
    // Zero all values.
    player->id = 0;
    memset(player->username, 0, sizeof(player->username));

    return player;
}

/**
 * Moves the player in a direction based on the given inputs.
 * 
 * @param inputs The client side inputs which have been sent to the server.
 */
void move_player(char *inputs)
{
    if (inputs[INPUT_W] || inputs[INPUT_SPACE])
    {
        // Jump
    }

    if (inputs[INPUT_A])
    {
        // Move left
    }

    if (inputs[INPUT_D])
    {
        // Move right
    }
}