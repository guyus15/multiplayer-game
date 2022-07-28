/**
 * @file client.h
 * @brief Specifies the functionality behind connecting to the server and 
 * sending and recieving data to and from it.
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <player.h>

#define TRUE 1
#define FALSE 0

extern int sockfd;
extern int should_send_input;

extern player_t local_player;
extern player_t *players;
extern int player_size;

#endif
