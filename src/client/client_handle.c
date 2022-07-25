/**
 * @file client_handle.c
 * @brief Specifies function to handle and receive packets from the server.
 */

#include <client/client_handle.h>
#include <client/client_send.h>
#include <client/client.h>
#include <stdio.h>

extern client_t local_client;
extern client_t clients[7];

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

    send_welcome_received(client_id);
}

/**
 * A function used to handle packets of type SPAWN_PLAYER.
 *
 * @param packet A pointer to the received packet.
 */
static void spawn_player(packet_t *packet)
{

    printf("Spawning a player.\n");
}
