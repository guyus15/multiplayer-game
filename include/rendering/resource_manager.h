#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <rendering/shader.h>
#include <rendering/texture.h>

shader_t *load_shader(const char *name,
                      const char *vertex_shader_path,
                      const char *fragment_shader_path);
shader_t *get_shader(const char *name);

texture_t *load_texture(const char *name,
                        const char *file_path,
                        int alpha);
texture_t *get_texture(const char *name);

#endif