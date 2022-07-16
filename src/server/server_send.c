/**
 * @file server_send.c
 * @brief Specifies function to handle sending packets from the server to
 * clients.
 */

#include <server/server_send.h>
#include <server/server.h>
#include <packet.h>
#include <stdio.h>
#include <stdlib.h>

client_t clients[MAXCLIENTS];

// Forward declarations
static void send_data(int to_client, packet_t *packet);

/**
 * Sends a welcome packet to a specific client.
 * 
 * @param to_client The ID of the target client.
 */
void send_welcome_message(int to_client)
{
    packet_t *welcome_packet = create_packet();
    set_packet_type(welcome_packet, WELCOME);

    send_data(to_client, welcome_packet);
}

/**
 * Sends a given packet to a specific client. 
 * 
 * @param to_client The ID of the target client.
 * @param packet The packet to send.
 */
static void send_data(int to_client, packet_t *packet)
{
    printf("Sending data to client with ID: %d\n", clients[0].id);
    exit(-1);
}