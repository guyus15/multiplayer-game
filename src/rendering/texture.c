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

void generate(texture_t *texture,
              unsigned int width,
              unsigned int height,
              unsigned char *data)
{
    texture->width = width;
    texture->height = height;

    // Bind texture
    glGenTextures(1, &(texture->id));
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexImage2D(GL_TEXTURE_2D, 0,
                 texture->internal_format,
                 texture->width,
                 texture->height,
                 0,
                 texture->image_format,
                 GL_UNSIGNED_BYTE,
                 data);

    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->filter_max);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void bind(texture_t *texture)
{
    glBindTexture(GL_TEXTURE_2D, texture->id);
}