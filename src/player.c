/**
 * @file player.h
 * @brief A file which specifies related functions for the player.
 */

#include <player.h>
#include <input.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
    glm_vec2_zero(player->position);
    glm_vec2_zero(player->velocity);

    return player;
}

/**
 * Moves a player in a direction based on the given inputs.
 * 
 * @param *player_t The player to move.
 * @param inputs The client side inputs which have been sent to the server.
 */
void move_player(player_t *player, char *inputs)
{
    if (inputs[INPUT_W] || inputs[INPUT_SPACE])
    {
        // Jump
        printf("Player %d should be Jumping!\n", player->id);
        player->position[1] += 10; // Temporary jump height
    }

    if (inputs[INPUT_A])
    {
        // Move left
        printf("Player %d should be Moving Left!\n", player->id);
        player->position[0] += 1; // Temporary move speed
    }

    if (inputs[INPUT_D])
    {
        // Move right
        printf("Player %d should be Moving Right!\n", player->id);
        player->position[0] -= 1; // Temporary move speed
    }
    
    // TODO: replace direct position manipulation with velocity
    // vector.
}