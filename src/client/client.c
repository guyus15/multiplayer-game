/**
 * @file client.c
 * @brief Specifies the functionality behind connecting to the server and 
 * sending and recieving data to and from it.
 */

#include <client/client.h>
#include <packet.h>
#include <errno.h>
#include <game.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <poll.h>
#include <client/client_handle.h>

GLFWwindow *context;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <address> <port>\n", argv[0]);
        exit(0);
    }

    initialise_game();

    int status, activity;
    struct pollfd pollfd;
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

    pollfd.fd = sockfd;
    pollfd.events = POLLIN;

    while (!glfwWindowShouldClose(context))
    {   
        update();

        // Check if sockfd has stuff to read from (server has sent data)
        activity = poll(&pollfd, 1, 0);

        if (activity == -1)
        {
            perror("poll");
            continue;
        } else if (activity == 0)
        {
            continue;
        }
        
        // Read from sockfd (the server data)
        packet_t *receive_packet = create_packet();
        if ((recv(sockfd, receive_packet, sizeof(packet_t), 0)) == -1)
        {
            perror("recv");
            continue;
        }

        // Handle the received packet.
        handle_packet(receive_packet);
    }
        
    return 0;
}