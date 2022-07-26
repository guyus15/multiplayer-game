/**
 * @file game.c
 * @brief Provides functions for rendering the game world to the 
 * client application.
 */

#include <glad/glad.h> // This has to be first
#include <game.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <client/client.h>
#include <client/client_send.h>
#include <input.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Forward declaration
static void error_callback(int error, const char *description);

/**
 * Creates and configures a GLFW window context to prepare 
 * for rendering.
 */
void initialise_game()
{
    /*
     * Setting up GLFW
     */

    if (glfwInit() == 0)
    {
        perror("glfwInit");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glfwSetErrorCallback(error_callback);

    context = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Client", NULL, NULL);

    if (context == 0)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(context);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialise OpenGL context.\n");
        exit(EXIT_FAILURE);
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

/**
 * A function called at every frame of the game.
 * Rendering and input can be handled here.
 */
void update()
{
    // Rendering
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(context);

    // Poll and process events.
    glfwPollEvents();

    // Get player input and send to the server.

    if (should_send_input)
    {
        printf("Sending input packet!\n");
        char inputs[INPUT_SIZE];
        handle_input(context, inputs);
        send_player_input(inputs, INPUT_SIZE);
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