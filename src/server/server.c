/**
 * @file server.c
 * @brief Specifies the functionality behind managing connections, and sending
 * and receiving data to and from clients.
 */

#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <GLFW/glfw3.h>
#include <packet.h>
#include <player.h>
#include <server/server.h>
#include <server/server_send.h>
#include <server/server_handle.h>

#define TICKS_PER_SEC 30

// Forward declations
static void error_callback(int error, const char *description);
static void get_ip_string(const struct sockaddr *sa, char *s, size_t maxlen);
static void handle_connection();
static void handle_activity();
static void reset_socket_set();

static fd_set readfds;
static char address[INET_ADDRSTRLEN];
static int status, master_sockfd, sockfd,
           newsockfd, max_sockfd, activity;
static struct addrinfo hints, *result, *rp;
static struct sockaddr_storage peer_addr;
static socklen_t peer_addr_len;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(0);
    }
    
    /*
     * Setting up GLFW
     */
    GLFWwindow *offscreen_context;

    if (glfwInit() == 0)
    {
        perror("glfwInit");
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    offscreen_context = glfwCreateWindow(100, 100, "Server", NULL, NULL);

    if (offscreen_context == 0)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(offscreen_context);

    /*
     * Set up socket to listen for connections
     */

    // Zero the clients array
    memset(clients, 0, sizeof(clients));

    // Set up the IDs for each of the clients in the clients array.
    for (int i = 0; i < MAXCLIENTS; i++)
    {   
        clients[i].id = i;
    }

    // Set up hints
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
        master_sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (master_sockfd == -1)
        {
            continue;
        }

        if (bind(master_sockfd, rp->ai_addr, rp->ai_addrlen) == 0)
        {
            // If we have reached here, we have successfully binded,
            // so we can break.
            break; 
        }

        close(master_sockfd);
    }

    // Free linked list
    freeaddrinfo(result);

    if (rp == NULL)
    {
        // No address succeeded to bind
        fprintf(stderr, "Server: Failed to bind\n");
        exit(EXIT_FAILURE);
    }

    if (listen(master_sockfd, BACKLOG) == -1)
    {
        perror("listen");
        exit(-1);
    }

    printf("Server: Listening for connections...\n");

    /*
     * Main server loop
     */

    double current_time = glfwGetTime(), last_time = current_time;
    double target_interval = 1.0 / TICKS_PER_SEC;

    while (!glfwWindowShouldClose(offscreen_context))
    {
        current_time = glfwGetTime();
        if ((current_time - last_time) > target_interval)
        {
            last_time = current_time;
        } else {
            continue;
        }

        reset_socket_set();

        struct timeval timeout = {0, 0};
        activity = select(max_sockfd + 1, &readfds, NULL, NULL, &timeout);

        if ((activity < 0) && (errno != EINTR))
        {
            perror("select");
        }

        if (FD_ISSET(master_sockfd, &readfds))
        {
            // Check for activity on the master socket, if there is some,
            // this is an incoming connection.
            handle_connection();

        }  

        // Otherwise, it is some operation on another socket.
        handle_activity();
    }
    
    close(newsockfd);

    return 0;
}

/**
 * Sends a player into the game and informs all other clients of their 
 * existence.
 *
 * @param client_id The ID of the client that is being sent in to the game.
 * @param player_name The name of the player being sent into the game.
 */
void send_into_game(int client_id, const char *player_name)
{   
    printf("Server: Sending player '%s' into the game\n", player_name);

    // Create a player
    clients[client_id].player = create_player();
    clients[client_id].player->id = client_id;   

    // Check all other clients for players and spawn them locally.
    
    client_t current_client;
    
    for (int i = 0; i < MAXCLIENTS; i++)
    {
        current_client = clients[i];

        if (current_client.player != NULL)
        {
            if (current_client.id != client_id)
            {
                send_spawn_player_message(client_id, current_client.player);
            }
        }
    }

    // Let all other clients know of this player's existence (including himself).
    for (int i = 0; i < MAXCLIENTS; i++)
    {
        current_client = clients[i];

        if (current_client.player != NULL)
        {

            send_spawn_player_message(current_client.id, clients[client_id].player);
        }
    }
}

/**
 * An error callback function for handling GLFW errors.
 * 
 * @param error The ID of the error.
 * @param description A description of the error.
 */
static void error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW error: %s\n", description);
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
 * Handles an incoming connection TCP on the master socket.
 */
static void handle_connection()
{ 
    peer_addr_len = sizeof(peer_addr);

    if ((newsockfd = accept(master_sockfd,
                (struct sockaddr *)&peer_addr, 
                (socklen_t*)&peer_addr_len)) == -1)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAXCLIENTS; i++)
    {
        if (clients[i].sockfd == 0)
        {
            clients[i].sockfd = newsockfd;

            // Send welcome message to the client upon successful connection
            send_welcome_message(i);

            break;
        }
    }

    get_ip_string((struct sockaddr *)&peer_addr, address, peer_addr_len);
    printf("Server: Received connection from %s\n", address);
}

/**
 * Checks each socket for activity, if a socket is active,
 * then it will handle it appropriately.
 */
static void handle_activity()
{  
    for (int i = 0; i < MAXCLIENTS; i++)
    {
        sockfd = clients[i].sockfd;

        if (FD_ISSET(sockfd, &readfds))
        {
            packet_t *packet = create_packet();            
            status = recv(sockfd, (packet_t *)packet, sizeof(packet_t), 0);

            if (status == 0)
            {   
                // Nothing has been read, so handle a client disconnection.
                printf("Server: A client disconnected\n");

                close(sockfd);
                clients[i].sockfd = 0;
            } else if (status == -1)
            {
                perror("recv");
                continue;
            } else 
            {
                // Server has read some data, so handle a received packet.
                handle_packet(clients[i].id, packet);
            }
        } 
    }
}

/**
 * Reset the socket set to check for socket activity.
 */
static void reset_socket_set()
{ 
    // Clears the socket set
    FD_ZERO(&readfds);

    // Add the master socket to the set
    FD_SET(master_sockfd, &readfds);
    max_sockfd = master_sockfd;

    for (int i = 0; i < MAXCLIENTS; i++)
    {
        sockfd = clients[i].sockfd;

        if (sockfd > 0)
        {
            FD_SET(sockfd, &readfds);
        }

        if (sockfd > max_sockfd)
        {
            max_sockfd = sockfd;
        }
    }
}
