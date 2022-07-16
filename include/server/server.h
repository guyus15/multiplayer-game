#ifndef SERVER_H
#define SERVER_H

/**
 * Encapsulates client-related data.
 */
typedef struct client_type
{
    int id;
    int sockfd;
} client_t;

#endif