/**
 * @file debug.h
 * @brief Provides functions to provide debugging facilities to the application.
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <glad/glad.h>

#define gl_check_error() gl_check_error_(__FILE__, __LINE__);

GLenum gl_check_error_(const char *file, int line);

#endif