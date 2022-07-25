/**
 * @file server_handle.c
 * @brief Specifies functions to handle receiving specific packets.
 */

#include <server/server_handle.h>
#include <server/server.h>
#include <stdio.h>
#include <string.h>
#include <input.h>

// Forward declarations
static void do_nothing(int from_client, packet_t *packet);
static void welcome_received(int from_client, packet_t *packet);
static void player_input(int from_client, packet_t *packet);

/**
 * Handles an incoming packet by calling an associated function.
 *
 * @param from_client The ID of the client the packet was received from.
 * @param *packet A pointer to the received packet.
 */
void handle_packet(int from_client, packet_t *packet)
{
    // TODO: Do some memory management after we're done with the packet.
    // Otherwise everytime a packet is received, more memory will be used up.

    switch (packet->type)
    {
        case NONE:
            do_nothing(from_client, packet);
            break;
        case WELCOME_RECEIVED:
            welcome_received(from_client, packet);
            break;
        case PLAYER_INPUT:
            player_input(from_client, packet);
            break;
        default:
            do_nothing(from_client, packet);
            break;
    }
}

/**
 * A function used to do nothing when a packet with type NONE
 * is received.
 *
 * @param from_client The ID of the client the packet was received from.
 * @param *packet A pointer to the received packet.
 */
static void do_nothing(int from_client, packet_t *packet)
{
    return;
}

/**
 * A function used to handle packets of type WELCOME_RECEIVED.
 *
 * @param from_client The ID of the client the packet was received from.
 * @param *packet A pointer to the received packet.
 */
static void welcome_received(int from_client, packet_t *packet)
{
    printf("Server: WELCOME_MESSAGE_RECEIVED packet received from client %d\n", from_client);

    int16_t received_id;
    read_int16(packet, &received_id);

    if (from_client != received_id)
    {
        fprintf(stderr, "Server: Client %d assumed the wrong ID.\n", from_client);
    }

    char player_name[30];

    char current;
    read_byte(packet, &current);
    player_name[0] = current;
    for (int i = 0; current != '\0'; i++)
    {
        read_byte(packet, &current);
        player_name[i + 1] = current;
    }

    send_into_game(from_client, (const char *)player_name);
}

/**
 * A function used to handle packets of type PLAYER_INPUT.
 * 
 * @param from_client The ID of the client the packet was received from.
 * @param packet A pointer to the received packet.
 */
static void player_input(int from_client, packet_t *packet)
{
    char inputs[INPUT_SIZE];
    memset(inputs, 0, INPUT_SIZE);

    char current;
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        read_byte(packet, &current);
        inputs[i] = current;
    }
}
