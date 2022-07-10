#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <packet.h>
#include <server/server_handle.h>

#define MAXCLIENTS 10
#define BACKLOG 10

typedef struct client_type
{
    int sockfd;
} client_t;

static client_t clients[MAXCLIENTS];

// Forward declations
static void get_ip_string(const struct sockaddr *sa, char *s, size_t maxlen);
static void handle_connection(int sockfd);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(0);
    }
    
    int status, sockfd, newsockfd;
    struct addrinfo hints, *result, *rp;
    struct sockaddr_storage peer_addr;
    socklen_t peer_addr_len;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    if ((status = getaddrinfo(NULL, argv[1], &hints, &result)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(-1);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (sockfd == -1)
        {
            continue;
        }

        if (bind(sockfd, rp->ai_addr, rp->ai_addrlen) == 0)
        {
            // If we have reached here, we have successfully binded,
            // so we can break.
            break; 
        }

        close(sockfd);
    }

    // Free linked list
    freeaddrinfo(result);

    if (rp == NULL)
    {
        // No address succeeded to bind
        fprintf(stderr, "Server: Failed to bind\n");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(-1);
    }

    printf("Server: Listening for connections...\n");

    while (1)
    {
        peer_addr_len = sizeof(peer_addr);

        newsockfd = accept(sockfd, (struct sockaddr *)&peer_addr, &peer_addr_len);
        if (newsockfd == -1)
        {
            perror("accept");
            continue;
        }

        // Recieved connection

        char address[INET6_ADDRSTRLEN];
        get_ip_string((struct sockaddr *)&peer_addr, address, INET6_ADDRSTRLEN);

        printf("Server: Received connection from %s\n", address);
        
        pid_t pid = fork();
        
        if (pid == -1) // Forking failed
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0) // This is the child process
        {
            close(sockfd); // Close the unused socket.

            printf("Thank you main process! I am now handling socket %d.\n", newsockfd);
            handle_connection(newsockfd);
        }
    }
    
    close(newsockfd);

    return 0;
}

/**
 * Returns the IP of a given sockaddr structure.
 *
 * @param *sa The sockaddr structure source of the IP.
 * @param *s A char buffer in which to write the IP.
 * @param maxlen The maximum length of the buffer to write to.
 */
static void get_ip_string(const struct sockaddr *sa, char *s, size_t maxlen)
{
    switch(sa->sa_family)
    {
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr), s, maxlen);
            break;

        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr), s, maxlen);
            break;

        default:
            fprintf(stderr, "get_ip_string: Unknown AF\n");
            exit(-1);
    }
}

/**
 * Handle an incoming TCP connection
 *
 * @param sockfd The socket file descriptor for the socket created with accept().
 */
static void handle_connection(int sockfd)
{
    packet_t *packet = create_packet(); // Allocate memory for received packet
            
    while (1)
    {
        if ((recv(sockfd, (void *)packet, sizeof(packet_t), MSG_WAITALL)) == -1)
        {
            perror("recv");
            continue;
        }
 
        printf("Packet size is: %ld\n", packet->size);

        handle_packet(0, packet);
    }
}
