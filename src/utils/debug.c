/**
 * @file debug.c
 * @brief Provides functions to provide debugging facilities to the application.
 */

#include <utils/debug.h>
#include <stdio.h>
#include <string.h>

/**
 * Prints a string corresponding to an error code and returns
 * the error code.
 * 
 * @param file The name of the file to print in the output.
 * @param line The line number of to display in the output.
 * @return GLenum The error code.
 */
GLenum gl_check_enum_(const char *file, int line)
{
    GLenum error_code;

    while ((error_code = glGetError()) != GL_NO_ERROR)
    {
        char error_text[128];

        switch (error_code)
        {
        case GL_INVALID_ENUM:
            strcpy(error_text, "INVALID_ENUM");
            break;
        case GL_INVALID_VALUE:
            strcpy(error_text, "INVALID_VALUE");
            break;
        case GL_INVALID_OPERATION:
            strcpy(error_text, "INVALID_OPERATION");
            break;
        case GL_STACK_OVERFLOW:
            strcpy(error_text, "STACK_OVERFLOW");
            break;
        case GL_STACK_UNDERFLOW:
            strcpy(error_text, "STACK_UNDERFLOW");
            break;
        case GL_OUT_OF_MEMORY:
            strcpy(error_text, "OUT_OF_MEMORY");
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            strcpy(error_text, "INVALID_FRAMEBUFFER_OPERATION");
            break;
        }

        fprintf(stderr, "%s | %s (%d)\n", error_text, file, line);
    }

    return error_code;
}
