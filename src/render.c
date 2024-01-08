#include "render.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fcntl.h>
#include <stdlib.h>

#include "core/logger.h"
#include "core/filesystem.h"

static void glfw_error_callback(int code, const char *description) {
    ERROR("%s: %d", description, code);
}

static void glfw_window_size_callback(GLFWwindow *window, int width, int height) {
    TRACE("Window resized: (%i, %i)", width, height);
}

static void glfw_window_focus_callback(GLFWwindow *window, int focused) {
    if(focused) {
        TRACE("Window gained focus");
    } else {
        TRACE("Window lost focus");
    }
}

static void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

static void GLAPIENTRY gl_debug_message_callback(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar *message, const void *user_parameters) {
    ERROR("%s", message);
}

static unsigned int r_compile_shader(unsigned int type, const char *src) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        /* ERROR("Failed to compile shader\n%s", message); */
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int r_create_shader(struct Shader_Source source) {
    unsigned int program = glCreateProgram();
    unsigned int vs = r_compile_shader(GL_VERTEX_SHADER, source.vertex);
    unsigned int fs = r_compile_shader(GL_FRAGMENT_SHADER, source.fragment);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void r_init_glfw(void) {
    if(!glfwInit()) {
        const char *err;
        glfwGetError(&err);
        FATAL("Failed to initialize GLFW: %s", err);
    }

    glfwSetErrorCallback(glfw_error_callback);
    INFO("Running GLFW version %s", glfwGetVersionString());
}

GLFWwindow *r_create_window(int width, int height, const char *name) {
    GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
    if(window == NULL) {
        FATAL("Failed to create window");
    }

    int screen_width, screen_height;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);

    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window, glfw_window_size_callback);
    glfwSetWindowFocusCallback(window, glfw_window_focus_callback);

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        FATAL("Failed to initialize GLEW: %s", glewGetErrorString(err));
    }

    INFO("Running GLEW version %s", glewGetString(GLEW_VERSION));
    INFO("Running OpenGL version %s", glGetString(GL_VERSION));

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(gl_debug_message_callback, 0);

    glViewport(0, 0, screen_width, screen_height);
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);

    return window;
}

unsigned int r_init_shaders(struct Shader_Source src) {
    unsigned int shader = r_create_shader(src);

    glUseProgram(shader);
    return shader;
}

void r_load_vertices(struct Vec2D *vertices, size_t size) {
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_SHORT, GL_FALSE, sizeof(int16_t), 0);
}
