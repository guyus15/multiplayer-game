#ifndef SERVER_H
#define SERVER_H

#define MAXCLIENTS 10
#define BACKLOG 10

/**
 * Encapsulates client-related data.
 */
typedef struct client_type
{
    int id;
    int sockfd;
} client_t;

extern client_t clients[MAXCLIENTS];

#endif