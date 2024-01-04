#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fcntl.h>

#include "core/logger.h"

#define SHADER_PATH "resources/shaders/"

struct Shader_Source {
    const char *vertex;
    const char *fragment;
};

static void error_callback(int code, const char *description) {
    ERROR("%s: %d", description, code);
}

static void window_size_callback(GLFWwindow *window, int width, int height) {
    TRACE("Window resized: (%i, %i)", width, height);
}

static void window_focus_callback(GLFWwindow *window, int focused) {
    if(focused) {
        TRACE("Window gained focus");
    } else {
        TRACE("Window lost focus");
    }
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

static unsigned int compile_shader(unsigned int type, const char *src) {
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
        ERROR("Failed to compile shader: %s", message);
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int create_shader(struct Shader_Source source) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, source.vertex);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, source.fragment);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
