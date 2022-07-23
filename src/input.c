/**
 * @file input.c
 * @brief Contains functions which specify behaviour regarding handling player
 * input.
 */

#include <input.h>
#include <string.h>

/**
 * A function used to gather relevant inputs from the user
 * and send them to the server.
 * 
 * @param context A GLFW window context.
 */
void handle_input(GLFWwindow *context, char *inputs)
{
    memset(inputs, 0, INPUT_SIZE);

    if (glfwGetKey(context, GLFW_KEY_W) == GLFW_PRESS)
    {
        inputs[INPUT_W] = 1;
    }

    if (glfwGetKey(context, GLFW_KEY_A) == GLFW_PRESS)
    {
        inputs[INPUT_A] = 1;
    }

    if (glfwGetKey(context, GLFW_KEY_S) == GLFW_PRESS)
    {
        inputs[INPUT_S] = 1;
    }

    if (glfwGetKey(context, GLFW_KEY_D) == GLFW_PRESS)
    {
        inputs[INPUT_D] = 1;
    }
}