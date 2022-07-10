#ifndef SERVER_HANDLE_H
#define SERVER_HANDLE_H

#include <packet.h>

void handle_packet(int from_client, packet_t *packet);

#endif

