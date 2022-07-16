/**
 * @file client_handle.c
 * @brief Specifies function to handle and receive packets from the server.
 */

#ifndef CLIENT_HANDLE_H
#define CLIENT_HANDLE_H

#include <packet.h>

void handle_packet(packet_t *packet);

#endif