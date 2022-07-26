/**
 * @file client_handle.c
 * @brief Specifies function to handle and receive packets from the server.
 */

#include <client/client_handle.h>
#include <client/client_send.h>
#include <client/client.h>
#include <stdio.h>
#include <stdlib.h>

// Forward declarations
static void welcome(packet_t *packet);
static void spawn_player(packet_t *packet);

/**
 * Handles an incoming packet by calling an associated function.
 * 
 * @param packet A pointer to the the received packet.
 */
void handle_packet(packet_t *packet)
{
    switch(packet->type)
    {
        case NONE:
            break;
        case WELCOME:
            welcome(packet);
            break;
        case SPAWN_PLAYER:
            spawn_player(packet);
            break;
        default:
            break;
    }
}

/**
 * A function used to handle packets of type WELCOME.
 * 
 * @param packet A pointer to the received packet.
 */
static void welcome(packet_t *packet)
{
    printf("Client: Received a WELCOME packet.\n");

    int16_t client_id;
    read_int16(packet, &client_id);

    // Register the local player
    local_player.id = client_id;

    send_welcome_received(client_id);
}

/**
 * A function used to handle packets of type SPAWN_PLAYER.
 *
 * @param packet A pointer to the received packet.
 */
static void spawn_player(packet_t *packet)
{
    int16_t player_id;
    read_int16(packet, &player_id);

    printf("Client: Received a SPAWN_PLAYER packet. Client ID: %d\n", player_id);

    if (player_id == local_player.id)
    {
        // Spawning the local player.
        printf("Client: Spawning local player.\n");

        // TODO: Position the player in the world.


        // Allow the client to start sending input packets.
        should_send_input = TRUE;
        
    } else
    {
        // Spawning another client.

        player_size++;

        if (players == NULL)
        {
            // No clients currently exist, so allocate memory.
            players = (player_t *) malloc(sizeof(player_t));
        } else
        {
            // Clients already exist, so reallocate memory.
            players = (player_t *) realloc(players, player_size * sizeof(player_t));
        }

        players[player_size - 1].id = player_id;
    }
}
