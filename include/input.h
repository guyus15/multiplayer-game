/**
 * @file input.h
 * @brief Contains functions which specify behaviour regarding handling player
 * input.
 */

#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

typedef enum inputs_enum
{
    INPUT_W = 0,
    INPUT_A,
    INPUT_S,
    INPUT_D,
    INPUT_SPACE,
    INPUT_SIZE
} inputs;

void handle_input(GLFWwindow *context, char *inputs);

#endif
