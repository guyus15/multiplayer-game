#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <rendering/shader.h>

shader_t *load_shader(const char *name,
                      const char *vertex_shader_path,
                      const char *fragment_shader_path);
shader_t *get_shader(const char *name);

#endif