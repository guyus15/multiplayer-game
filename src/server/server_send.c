/**
 * @file server_send.c
 * @brief Specifies function to handle sending packets from the server to
 * clients.
 */

#include <server/server_send.h>
#include <server/server.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <packet.h>
#include <stdio.h>

client_t clients[MAXCLIENTS];

// Forward declarations
static void send_data(int to_client, packet_t *packet);
static void send_data_to_all(packet_t *packet);
static void send_data_to_all_except(int except_client, packet_t *packet);

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
 * Sends a spawn player packet to a specific client.
 *
 * @param to_client The ID of the target client.
 */
void send_spawn_player_message(int to_client, player_t *player)
{
    packet_t *spawn_packet = create_packet();
    set_packet_type(spawn_packet, SPAWN_PLAYER);

    

    send_data(to_client, spawn_packet);
}

/**
 * Sends a given packet to a specific client. 
 * 
 * @param to_client The ID of the target client.
 * @param packet A pointer to the packet to send.
 */
static void send_data(int to_client, packet_t *packet)
{
    client_t client;
    int id;

    // Look for the client ID in the client list.
    for (int i = 0; i < MAXCLIENTS; i++)
    {
        id = clients[i].id;

        if (id == to_client)
        {
            client = clients[i];
            break;
        }
    }
    
    if ((send(client.sockfd, packet, sizeof(packet_t), 0)) == -1)
    {
        perror("send");
    }
}

/**
 * Sends a given packet to every connected client.
 * 
 * @param packet A pointer to the packet to send.
 */
static void send_data_to_all(packet_t *packet)
{
    int sockfd;

    for (int i = 0; i < MAXCLIENTS; i++)
    {
        sockfd = clients[i].sockfd;

        if (sockfd == 0)
        {
            continue;
        }

        if ((send(sockfd, packet, sizeof(packet_t), 0)) == -1)
        {
            perror("send");
            continue;
        }
    }
}

/**
 * Sends a given packet to every connected client except
 * the client associated with the ID of except_client.
 * 
 * @param except_client The client to exclude from the sending of data.
 * @param packet A pointer to the packet to send.
 */
static void send_data_to_all_except(int except_client, packet_t *packet)
{
    int id, sockfd;

    for (int i = 0; i < MAXCLIENTS; i++)
    {
        id = clients[i].id;
        sockfd = clients[i].sockfd;

        if (sockfd == 0 || id == except_client)
        {
            continue;
        }

        if ((send(sockfd, packet, sizeof(packet), 0)) == -1)
        {
            perror("send");
            continue;
        }
    }
}
