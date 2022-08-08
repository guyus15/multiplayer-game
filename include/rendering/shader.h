#ifndef SHADER_H
#define SHADER_H

#include <stdbool.h>
#include <cglm/cglm.h>

typedef struct shader_type
{
    unsigned int id;
} shader_t;

void compile_shader(shader_t *shader,
                    const char *vertex_shader_source,
                    const char *fragment_shader_source);
void use_shader(shader_t *shader);
void set_bool(shader_t *shader, const char *name, int value);
void set_int(shader_t *shader, const char *name, int value);
void set_float(shader_t *shader, const char *name, float value);
void set_mat4(shader_t *shader, const char *name, mat4 value);
void set_vec3(shader_t *shader, const char *name, vec3 value);

#endif