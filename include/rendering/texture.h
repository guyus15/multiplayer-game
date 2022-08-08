/**
 * @file texture.h
 * @brief Specifies functions regarding texture management.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct texture_type
{
    unsigned int id;
    unsigned int width, height;   // Width and height of loaded image in pixels.
    unsigned int internal_format; // Format of texture object.
    unsigned int image_format;    // Format of loaded image.
    unsigned int wrap_s;          // Wrapping mode on S axis.
    unsigned int wrap_t;          // Wrapping mode on T axis.
    unsigned int filter_min;      // Filtering mode if texture pixels < screen pixels.
    unsigned int filter_max;      // Filtering mode if texture pixels > screen_pixels;
} texture_t;

texture_t *create_texture();

void generate(texture_t *texture, unsigned int width, unsigned int height, unsigned char *data);
void bind;

#endif 