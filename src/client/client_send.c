/**
 * @file client_send.h
 * @brief Specifies functions to handle sending packets from the client to
 * the server.
 */

#include <client/client.h>
#include <client/client_send.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <packet.h>

int sockfd;

// Forward declarations
static void send_data(packet_t *packet);

void send_welcome_received()
{
    packet_t *welcome_received_pckt = create_packet();
    set_packet_type(welcome_received_pckt, WELCOME_RECEIVED);

    send_data(welcome_received_pckt);
}

static void send_data(packet_t *packet)
{
    if ((send(sockfd, packet, sizeof(packet_t), 0)) == -1)
    {
        perror("send");
    }
}