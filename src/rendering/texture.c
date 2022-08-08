/**
 * @file texture.c
 * @brief Specifies functions regarding texture management.
 */

#include <rendering/texture.h>
#include <glad/glad.h>
#include <stdlib.h>
#include <string.h>

texture_t *create_texture()
{
    texture_t *texture = (texture_t *) malloc(sizeof(texture_t));
    memset(texture, 0, sizeof(texture_t));

    texture->internal_format = GL_RGB;
    texture->image_format = GL_RGB;
    texture->wrap_s = GL_REPEAT;
    texture->wrap_t = GL_REPEAT;
    texture->filter_min = GL_LINEAR;
    texture->filter_max = GL_LINEAR;

    return texture;
}
