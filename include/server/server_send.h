/**
 * @file server_send.h
 * @brief Specifies function to handle sending packets from the server to
 * clients.
 */

#ifndef SERVER_SEND_H
#define SERVER_SEND_H

void send_welcome_message(int to_client);
void send_spawn_player_message(int to_client);

#endif
