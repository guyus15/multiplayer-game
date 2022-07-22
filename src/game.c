#include <game.h>
#include <stdlib.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Forward declaration
static void error_callback(int error, const char *description);

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

    glfwSetErrorCallback(error_callback);

    context = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Client", NULL, NULL);

    if (context == 0)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(context);
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
