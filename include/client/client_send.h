/**
 * @file client_send.h
 * @brief Specifies functions to handle sending packets from the client to
 * the server.
 */

#ifndef CLIENT_SEND_H
#define CLIENT_SEND_H

#include <stddef.h>
#include <stdint.h>

void send_welcome_received(int16_t received_id);
void send_player_input(char *inputs, size_t size);

#endif