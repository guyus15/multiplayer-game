#include <rendering/shader.h>
#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

#define INFO_LOG_LENGTH 512

void compile_shader(shader_t *shader,
                    const char *vertex_shader_source,
                    const char *fragment_shader_source)
{
    int success;
    char info_log[INFO_LOG_LENGTH];

    unsigned int vertex_shader, fragment_shader, shader_program;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    shader_program = glCreateProgram();

    glShaderSource(vertex_shader, 1, (const char * const *)&vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    glShaderSource(fragment_shader, 1, (const char * const *)&fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, INFO_LOG_LENGTH, NULL, info_log);
        fprintf(stderr, "Error: Vertex shader compilation failed.\n%s\n", info_log);
        exit(EXIT_FAILURE);
    }

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, INFO_LOG_LENGTH, NULL, info_log);
        fprintf(stderr, "Error: Fragment shader compilation failed.\n%s\n", info_log);
        exit(EXIT_FAILURE);
    }

    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    glLinkProgram(shader_program);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shader_program, INFO_LOG_LENGTH, NULL, info_log);
        fprintf(stderr, "Error: Shader program linking failed.\n%s\n", info_log);
        exit(EXIT_FAILURE);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    shader->id = shader_program;
}

void use_shader(shader_t *shader)
{
    glUseProgram(shader->id);
}

void set_bool(shader_t *shader, const char *name, int value)
{
    glUniform1i(glGetUniformLocation(shader->id, name), value);
}

void set_int(shader_t *shader, const char *name, int value)
{
    glUniform1i(glGetUniformLocation(shader->id, name), value);
}

void set_float(shader_t *shader, const char *name, float value)
{
    glUniform1f(glGetUniformLocation(shader->id, name), value);
}

void set_mat4(shader_t *shader, const char *name, mat4 value)
{
    float values[] = 
    {
        value[0][0], value[0][1], value[0][2], value[0][3],
        value[1][0], value[1][1], value[1][2], value[1][3],
        value[2][0], value[2][1], value[2][2], value[2][3],
        value[3][0], value[3][1], value[3][2], value[3][3]
    };

    glUniformMatrix4fv(glGetUniformLocation(shader->id, name), 1, GL_FALSE, (const float *)&values);}

void set_vec3(shader_t *shader, const char *name, vec3 value)
{
    float values[] =
    {
        value[0],  value[1],  value[2]
    };

    glUniform3fv(glGetUniformLocation(shader->id, name), 1, (const float *)&values);
}
