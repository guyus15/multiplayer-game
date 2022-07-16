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
    packet_t *packet = create_packet();
    set_packet_type(packet, WELCOME_RECEIVED);

    char player_name[30] = "Test Name\0";

    for (int i = 0; player_name[i] != '\0'; i++)
    {
        write_byte(packet, player_name[i]);
    }

    send_data(packet);
}

static void send_data(packet_t *packet)
{
    if ((send(sockfd, packet, sizeof(packet_t), 0)) == -1)
    {
        perror("send");
    }
}
