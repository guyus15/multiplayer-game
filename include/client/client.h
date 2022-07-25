/**
 * @file client.h
 * @brief Specifies the functionality behind connecting to the server and 
 * sending and recieving data to and from it.
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <player.h>

extern int sockfd;

/**
 * Encapsulates client-related data.
 */
typedef struct client_type
{
    int id;
    player_t *player;
} client_t;

#endif
