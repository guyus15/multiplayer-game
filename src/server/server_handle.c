/**
 * @file server_handle.c
 * @brief Specifies functions to handle receiving specific packets.
 */

#include <server/server_handle.h>
#include <stdio.h>

// Forward declarations
static void do_nothing(int from_client, packet_t *packet);
static void welcome_received(int from_client, packet_t *packet);

/**
 * Handles an incoming packet by calling an associated function.
 *
 * @param from_client The ID of the client the packet was received from.
 * @param *packet A pointer to the received packet.
 */
void handle_packet(int from_client, packet_t *packet)
{
    switch (packet->type)
    {
        case NONE:
            do_nothing(from_client, packet);
            break;
        case WELCOME_RECEIVED:
            welcome_received(from_client, packet);
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
    printf("The client has told us they have received the welcome message\n");
}
￼
