#ifndef SHADER_H
#define SHADER_H

#include <cglm/cglm.h>

typedef struct shader_type
{
    unsigned int;
} shader_t;

void compile_shader(shader_t *shader,
                    const char *vertex_shader_source,
                    const char *fragment_shader_source);
void use_shader(shader_t *shader);

#endif