/**
 * @file game.h
 * @brief Provides functions for rendering the game world to the 
 * client application.
 */

#ifndef GAME_H
#define GAME_H

#include <GLFW/glfw3.h>

#define INPUT_SIZE 4

extern GLFWwindow *context;

void initialise_game();
void update();

#endif