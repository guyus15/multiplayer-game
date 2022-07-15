/**
 * @file client.c
 * @brief Specifies the functionality behind connecting to the server and 
 * sending and recieving data to and from it.
 */

#include <packet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <address> <port>\n", argv[0]);
        exit(0);
    }

    int status, sockfd;
    struct addrinfo hints, *result, *rp;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(argv[1], argv[2], &hints, &result)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (sockfd == -1)
        {
            continue;
        }

        if ((connect(sockfd, (struct sockaddr *)rp->ai_addr, rp->ai_addrlen)) == -1)
        {
            close(sockfd);
            perror("client connect");
            continue;
        }
        
        // If we reach here, the socket has successfully connected to the 
        // server, so break.
        break;
    }

    if (rp == NULL)
    {
        fprintf(stderr, "Client: Connection failure\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    printf("Connected.\n");

    packet_t *packet = create_packet();
    
    set_packet_type(packet, WELCOME_RECEIVED);

    while (1)
    {   
        if ((send(sockfd, (void *)packet, sizeof(packet_t), 0)) == -1)
        {
            perror("send");
            continue;
        }
        
        printf("Packet sent!\n");
        
        // Send a disconnect message to the server.
        if ((send(sockfd, NULL, 0, 0)) == -1)
        {   
            perror("send");
            continue;
        }

        printf("Disconnected\n");

        close(sockfd);

        break;
    }
        
    return 0;
}
