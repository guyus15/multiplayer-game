/**
 * @file server.h
 * @brief Specifies the functionality behind managing connections, and sending
 * and receiving data to and from clients.
 */

#ifndef SERVER_H
#define SERVER_H

#include <player.h>

#define MAXCLIENTS 10
#define BACKLOG 10

/**
 * Encapsulates client-related data.
 */
typedef struct client_type
{
    int id, sockfd;
    player_t *player;
} client_t;

extern client_t clients[MAXCLIENTS];

void send_into_game(const char *player_name);

#endif
