/**
 * @file client_handle.c
 * @brief Specifies function to handle and receive packets from the server.
 */

#include <client/client_handle.h>
#include <stdio.h>

// Forward declarations
static void welcome(packet_t *packet);

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
    printf("Client: Received a welcome packet.");

    // TODO: respond to the server with a WELCOME_RECEIVED packet.
}