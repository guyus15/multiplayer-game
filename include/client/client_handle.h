/**
 * @file client_handle.h
 * @brief Specifies function to handle and receive packets from the server.
 */

#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H

#include <packet.h>
#include <player.h>

extern player_t local_player;
extern player_t *players;
extern int player_size;

void handle_packet(packet_t *packet);

#endif