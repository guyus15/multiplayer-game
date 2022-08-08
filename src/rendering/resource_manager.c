#include <rendering/resource_manager.h>
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define MAX_SOURCE_LENGTH 1024

typedef struct shader_entry_type
{
    char *name;
    shader_t *shader;
} shader_entry_t;

typedef struct texture_entry_type
{
    char *name;
    texture_t *texture;
} texture_entry_t;

static shader_entry_t *shaders;
static texture_entry_t *textures;

static int shader_count = 0;
static int texture_count = 0;

// Forward declarations
static void create_shader_entry();
static void create_texture_entry();
static shader_t *load_shader_from_file(const char *vertex_shader_path,
                                       const char *fragment_shader_path);
static texture_t *load_texture_from_file(const char *file_path, int alpha);

shader_t *load_shader(const char *name, 
                      const char *vertex_shader_path,
                      const char *fragment_shader_path)
{
    create_shader_entry();

    shader_entry_t *shader_entry = &(shaders[shader_count - 1]);

    size_t name_len = strlen(name);
    shader_entry->name = (char *) calloc(name_len, sizeof(char));
    strcpy(shader_entry->name, name);

    shader_entry->shader = load_shader_from_file(vertex_shader_path,
                                                 fragment_shader_path);

    return shader_entry->shader;
}

shader_t *get_shader(const char *name)
{
    shader_t *shader = NULL;

    for (int i = 0; i < shader_count; i++)
    {
        if (strcmp(shaders[i].name, name) == 0)
        {
            shader = shaders[i].shader;
            break;
        }
    }

    if (shader == NULL)
    {
        // No shader has been found, so exit with failure.
        fprintf(stderr, "Error: No shader found with name '%s'.\n", name);
        exit(EXIT_FAILURE);
    }

    return shader;
}

texture_t *load_texture(const char *name,
                        const char *file_path,
                        int alpha)
{
    create_texture_entry();

    texture_entry_t *texture_entry = &(textures[texture_count - 1]);

    size_t name_len = strlen(name);
    texture_entry->name = (char *) calloc(name_len, sizeof(char));
    strcpy(texture_entry->name, name);

    texture_entry->texture = load_texture_from_file(file_path, alpha);

    return texture_entry->texture;
}

texture_t *get_texture(const char *name)
{
    texture_t *texture = NULL;

    for (int i = 0; i < texture_count; i++)
    {
        if (strcmp(textures[i].name, name) == 0)
        {
            texture = textures[i].texture;
            break;
        }
    }

    if (texture == NULL)
    {
        // No texture has been found, so exit with failure.
        fprintf(stderr, "Error: No texture found with the name '%s'.\n", name);
        exit(EXIT_FAILURE);
    }

    return texture;
}

static void create_shader_entry()
{
    if (shader_count == 0)
    {
        shaders = (shader_entry_t *) malloc(sizeof(shader_entry_t));
        shader_count++;
    } else if (shader_count > 0)
    {
        shader_count++;
        shaders = (shader_entry_t *) realloc(shaders, sizeof(shader_entry_t) * shader_count);
    }

    memset(&(shaders[shader_count - 1]), 0, sizeof(shader_entry_t));
}

static void create_texture_entry()
{
    if (texture_count == 0)
    {
        textures = (texture_entry_t *) malloc(sizeof(texture_entry_t));
        texture_count++;
    } else if (texture_count > 0)
    {
        texture_count++;
        textures = (texture_entry_t *) realloc(textures, sizeof(texture_entry_t) * texture_count);
    }
}

static shader_t *load_shader_from_file(const char *vertex_shader_path,
                                       const char *fragment_shader_path)
{
    FILE *vertex_file, *fragment_file;

    vertex_file = fopen(vertex_shader_path, "r");

    if (vertex_file == NULL)
    {
        perror("fopen - vertex file");
        exit(EXIT_FAILURE);
    }

    fragment_file = fopen(fragment_shader_path, "r");

    if (fragment_file == NULL)
    {
        perror("fopen - fragment file");
        exit(EXIT_FAILURE);
    }

    char v_shader_src[MAX_SOURCE_LENGTH],
         f_shader_src[MAX_SOURCE_LENGTH];

    memset(v_shader_src, 0, sizeof(v_shader_src));
    memset(f_shader_src, 0, sizeof(f_shader_src));

    char *vertex_shader_source = v_shader_src;
    char *fragment_shader_source = f_shader_src;

    fseek(vertex_file, 0, SEEK_SET); 
    fseek(fragment_file, 0, SEEK_SET);

    fread(v_shader_src, sizeof(char), MAX_SOURCE_LENGTH, vertex_file);
    fread(f_shader_src, sizeof(char), MAX_SOURCE_LENGTH, fragment_file);

    fclose(vertex_file);
    fclose(fragment_file);

    shader_t *shader = (shader_t *) malloc(sizeof(shader_t));
    memset(shader, 0, sizeof(shader_t));

    compile_shader(shader, vertex_shader_source, fragment_shader_source);

    return shader;
}

static texture_t *load_texture_from_file(const char *file_path, int alpha)
{
    texture_t *texture = create_texture();

    if (alpha)
    {
        texture->internal_format = GL_RGBA;
        texture->image_format = GL_RGBA;
    }

    int width, height, nr_channels;
    unsigned char *data = stbi_load(file_path, &width, &height, &nr_channels, 0);

    if (data == NULL)
    {
        fprintf(stderr, "Error: Failed to load image at path '%s'.\n", file_path);
        exit(EXIT_FAILURE);
    }

    generate(texture, width, height, data);

    stbi_image_free(data);

    return texture;
}