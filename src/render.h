#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdint.h>
#include <stddef.h>

#define SHADER_PATH "resources/shaders/"

struct Shader_Source {
    const char *vertex;
    const char *fragment;
};

struct Vec2D {
    int16_t x;
    int16_t y;
};

void r_init_glfw(void);
GLFWwindow *r_create_window(int width, int height, const char *name);
unsigned int r_init_shaders(struct Shader_Source src);
void r_load_vertices(struct Vec2D *vertices, size_t size);

void initialize_rendering(void);
void create_window(int width, int height, const char *name);
void initialize_shaders(void);
