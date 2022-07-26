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

/**
 * Sends a welcome received packet to the server.
 */
void send_welcome_received(int16_t received_id)
{
    packet_t *packet = create_packet();
    set_packet_type(packet, WELCOME_RECEIVED);

    write_int16(packet, received_id);

    char player_name[30] = "Test Name\0";

    for (int i = 0; player_name[i] != '\0'; i++)
    {
        write_byte(packet, player_name[i]);
    }

    send_data(packet);
}

/**
 * Sends a packet containing the state of input
 * from the player. 
 * 
 * @param inputs A boolean array of inputs. 
 * @param size  The size of the array of inputs.
 */
void send_player_input(player_t *player, char *inputs, size_t size)
{
    packet_t *packet = create_packet();
    set_packet_type(packet, PLAYER_INPUT);

    write_int32(packet, player->id);

    for (int i = 0; i < size; i++)
    {
        write_byte(packet, inputs[i]);
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
